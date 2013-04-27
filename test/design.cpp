#include "model/order_book.hpp"
#include "model/order.hpp"

#include "disruptor/ring_buffer.hpp"
#include "disruptor/event_publisher.hpp"
#include "disruptor/exception_handler.hpp"
#include "disruptor/event_processor.hpp"

#include <sys/time.h>
#include <iostream>
#include <array>
#include <thread>
#include <future>

// The OrderBufferFactory is responsible for initializing the backing store for the RingBuffer.
class OrderBufferFactory : public market::disruptor::EventFactoryInterface<market::model::Order>
{ 
    public:
        market::model::Order*
        NewInstance(
            const int& size
        ) const
        {
            auto array = new market::model::Order[size];
            return array;
        }
};

// The OrderTranslator is responsible for marshaling input data into Order objects.
// This implementation creates a random order for testing purposes. 
class OrderTranslator : public market::disruptor::EventTranslatorInterface<market::model::Order>
{
    market::model::Order*
    TranslateTo(
        const int64_t& sequence,
        market::model::Order* order
    )
    {
        bool is_buy(rand() % 2);
        uint32_t delta = is_buy ? 1880 : 1884;
        market::book::Price price = (rand() % 10) + delta;
        market::book::Quantity qty = ((rand() % 10) + 1) * 100;
        order->initialize(is_buy, price, qty);
        return order;
    }
};

class OrderBatchHandler : public market::disruptor::EventHandlerInterface<market::model::Order>
{
    public:
        

        void OnEvent(
            const int64_t& sequence,
            const bool& end_of_batch,
            market::model::Order* order
        )
        {
            //if (event) { 
            //    event->set_value(sequence);
            //}
        };

        void OnStart() {}
        void OnShutdown() {}
};

class OrderProcessor : public market::disruptor::EventProcessorInterface<market::model::Order> 
{
    public:
        OrderProcessor(
            market::disruptor::SequenceBarrierInterface* barrier
        ) : barrier_(barrier),
            sequence_(market::disruptor::kInitialCursorValue)
        {}

        market::disruptor::Sequence*
        GetSequence() {
            return &sequence_;
        }

        void Halt() {}
        void Run() {
            try {
                barrier_->WaitFor(0L);
            } catch(...) {
                throw std::runtime_error("caught exception in OrderProcessor::Run()");
            }
            sequence_.set_sequence(sequence_.sequence() + 1L);
        }
    private:
        market::disruptor::PaddedSequence sequence_;
        market::disruptor::SequenceBarrierInterface* barrier_;
};

#if 0 
int run_test(market::model::OrderBook<5>& order_book, market::model::Order** orders, clock_t end) {
    int count = 0;
    market::model::Order** pp_order = orders;
    do {
        order_book.add(*pp_order);
        order_book.perform_callbacks();
        ++pp_order;
        if (*pp_order == NULL) {
            return -1;
        }
        ++count;
    } while (clock() < end);
    return (pp_order - orders);
}

bool build_and_run_test(uint32_t dur_sec, uint32_t num_to_try) {
  clock_t start = clock();
  clock_t stop = start + (dur_sec * CLOCKS_PER_SEC);

  int count = run_test(order_book, orders, stop);
  for (uint32_t i = 0; i <= num_to_try; ++i) {
    delete orders[i];
  }
  delete [] orders;
  if (count > 0) {
    std::cout << " - complete!" << std::endl;
    std::cout << "Inserted " << count << " orders in " << dur_sec << " seconds"
              << ", or " << count / dur_sec << " insertions per sec"
              << std::endl;
    uint32_t remain = order_book.bids().size() + order_book.asks().size();
    std::cout << "Run matched " << count - remain << " orders" << std::endl;
    return true;
  } else {
    std::cout << " - not enough orders" << std::endl;
    return false;
  }

  return count > 0;
}
#endif 

int main(int argc, char *argv[]) {
    int buffer_size = 1024 * 16;
    long iterations = 1000L * 1000L * 300;

    // std::unique_ptr<market::model::OrderBook<5>> order_book;

    std::cout << iterations << std::endl;

    auto input_buffer = new market::disruptor::RingBuffer<market::model::Order>(
        new OrderBufferFactory,
        buffer_size,
        market::disruptor::kSingleThreadedStrategy, // A single publisher thread
        market::disruptor::kBusySpinStrategy
    );

    std::vector<market::disruptor::Sequence*> sequence_to_track(0);
    std::unique_ptr<market::disruptor::ProcessingSequenceBarrier> barrier(input_buffer->NewBarrier(sequence_to_track));

    OrderBatchHandler order_handler;
    market::disruptor::IgnoreExceptionHandler<market::model::Order> order_exception_handler;
    market::disruptor::BatchEventProcessor<market::model::Order> processor(
        input_buffer,
        (market::disruptor::SequenceBarrierInterface*) barrier.get(),
        &order_handler,
        &order_exception_handler
    );

    std::thread consumer(std::ref<market::disruptor::BatchEventProcessor<market::model::Order>>(processor));

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    std::unique_ptr<OrderTranslator> translator(new OrderTranslator);
    market::disruptor::EventPublisher<market::model::Order> publisher(input_buffer);
    for (long i=0; i<iterations; i++) {
        publisher.PublishEvent(translator.get());
    }

    long expected_sequence = input_buffer->GetCursor();
    while (processor.GetSequence()->sequence() < expected_sequence) {}

    gettimeofday(&end_time, NULL);

    double start, end;
    start = start_time.tv_sec + ((double) start_time.tv_usec / 1000000);
    end = end_time.tv_sec + ((double) end_time.tv_usec / 1000000);

    std::cout.precision(15);
    std::cout << "Performance: ";
    std::cout << (iterations * 1.0) / (end - start) << " OPS" << std::endl;

    processor.Halt();
    consumer.join();
    
    return 0;
}
