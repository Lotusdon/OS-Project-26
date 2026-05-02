#include "Chef.h"
#include <iostream>
#include <chrono>
#include <thread>

chef::chef(order_queue& q, stats& s, int id)
    : queue(q), system_stats(s), chef_id(id) {}

void chef::run() {
    while (running) {

        stations.acquire();

        order o = queue.wait_and_pop();

        o.status = order_status::in_progress;

        std::cout << "chef " << chef_id << " started order " << o.order_id << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 + (o.order_id % 500)));

        o.status = order_status::done;

        std::cout << "chef " << chef_id << " finished order " << o.order_id << "\n";

        stations.release();
    }
}
