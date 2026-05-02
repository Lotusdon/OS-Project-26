#include "Waiter.h"
#include <iostream>
#include <chrono>

waiter::waiter(order_queue& q, stats& s, int id)
    : queue(q), system_stats(s), waiter_id(id) {}

void waiter::run() {
    int order_counter = 0;

    while (running) {
        order o;

        o.order_id = waiter_id * 1000 + order_counter++;
        o.customer_name = "customer_" + std::to_string(o.order_id);
        o.item_name = "burger";
        o.quantity = 1;
        o.price = 130.0;

        o.priority = (o.order_id % 5 == 0) ? order_priority::vip : order_priority::normal;
        o.status = order_status::pending;
        o.timestamp = std::chrono::steady_clock::now();

        queue.push(o);

        system_stats.total_orders++;

        std::cout << "waiter " << waiter_id << " created order " << o.order_id << "\n";

std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
