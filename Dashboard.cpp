#include "Dashboard.h"
#include <iostream>
#include <chrono>
#include <thread>

dashboard::dashboard(order_queue& q, stats& s)
    : queue(q), system_stats(s) {}

void dashboard::run() {

    while (running) {

        std::cout << "\033[2J\033[1;1H";

        std::cout << "=== RESTAURANT LIVE DASHBOARD ===\n\n";

        std::cout << "queue size      : " << queue.size() << "\n";
        std::cout << "total orders    : " << system_stats.total_orders.load() << "\n";
        std::cout << "completed       : " << system_stats.completed_orders.load() << "\n";
        std::cout << "cancelled       : " << system_stats.cancelled_orders.load() << "\n";

        std::cout << "\nsystem status: RUNNING\n";

        std::cout << "==================================\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
