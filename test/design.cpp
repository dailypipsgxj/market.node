#include "model/order_book.hpp"
#include "model/order.hpp"

#include "disruptor/ring_buffer.hpp"
#include "disruptor/event_publisher.hpp"

#include <iostream>
#include <array>
#include <thread>
#include <future>

#define BUFFER_SIZE 8192

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

class OrderTranslator : public market::disruptor::EventTranslatorInterface<market::model::Order>
{
    market::model::Order*
    TranslateTo(
        const int64_t& sequence,
        market::model::Order*
    )
    {
        return new market::model::Order(0,0,0);
    }
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
                throw std::runtime_error("catched exception in OrderProcessor::Run()");
            }
            sequence_.set_sequence(sequence_.sequence() + 1L);
        }
    private:
        market::disruptor::PaddedSequence sequence_;
        market::disruptor::SequenceBarrierInterface* barrier_;
};

int main(int argc, char *argv[]) {
    auto input_buffer = new market::disruptor::RingBuffer<market::model::Order>(
        new OrderBufferFactory,
        BUFFER_SIZE,
        market::disruptor::kSingleThreadedStrategy, // A single publisher thread
        market::disruptor::kBusySpinStrategy
    );

    auto publisher = new market::disruptor::EventPublisher<market::model::Order>(input_buffer);

    auto translator = new OrderTranslator();
    publisher->PublishEvent(translator);
    
    return 0;
}
