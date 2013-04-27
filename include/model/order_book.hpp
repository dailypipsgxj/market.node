#pragma once

#include <iostream>

#include "model/order.hpp"
#include "book/depth_order_book.hpp"

namespace market { 
    namespace model { 

        // @brief binding of DepthOrderBook template with Order pointer.
        template <int SIZE = 5>
        class OrderBook : public market::book::DepthOrderBook<market::model::Order*, SIZE> {
            public:
                typedef market::book::Callback<market::model::Order*> MarketCallback;
                typedef uint32_t FillId;

                OrderBook();

                // Override callback handling to update Order state
                virtual void perform_callback(MarketCallback& cb);
            private:
                FillId fill_id_;
        };

        template <int SIZE>
        OrderBook<SIZE>::OrderBook() : fill_id_(0)
        {}

        template <int SIZE>
        inline void
        OrderBook<SIZE>::perform_callback(MarketCallback& cb)
        {
            book::DepthOrderBook<Order*, SIZE>::perform_callback(cb);
            switch(cb.type) {
                case MarketCallback::cb_order_accept: {
                    cb.order->accept();
                    break;
                }
                case MarketCallback::cb_order_fill: {
                    // Increment fill ID once
                    ++fill_id_;
                    // Update the orders
                    market::book::Cost fill_cost = cb.fill_qty * cb.fill_price;
                    cb.matched_order->fill(cb.fill_qty, fill_cost, fill_id_);
                    cb.order->fill(cb.fill_qty, fill_cost, fill_id_);
                    break;
                }
                case MarketCallback::cb_order_cancel: {
                    cb.order->cancel();
                    break;
                }
                case MarketCallback::cb_order_replace: {
                    // Modify the order itself
                    cb.order->replace(cb.repl_size_delta, cb.repl_new_price);
                    break;
                }
                default: break;
            }
        }
    
   } // namespace model
} // namespace market
