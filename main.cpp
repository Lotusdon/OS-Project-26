
#include "OrderQueue.h"
#include "Waiter.h"
#include "Chef.h"
#include "KitchenManager.h"
#include "Dashboard.h"
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>
#include <semaphore>

std::atomic<bool> running(true);
std::counting_semaphore<10> stations(3);

stats system_stats;

int main() {

    order_queue queue;

    kitchen_manager manager(queue);
    dashboard dash(queue, system_stats);

    std::vector<std::thread> waiter_threads;
    std::vector<std::thread> chef_threads;

for (int i = 1; i <= 3; i++) {

        waiter_threads.emplace_back([&queue, &system_stats, i]() {

            waiter w(queue, system_stats, i);
            w.run();

        });
    }

    for (int i = 1; i <= 5; i++) {

        chef_threads.emplace_back([&queue, &system_stats, i]() {

            chef c(queue, system_stats, i);
            c.run();

        });
    }

    std::thread manager_thread(&kitchen_manager::run, &manager);
    std::thread dashboard_thread(&dashboard::run, &dash);

    std::cout << "press ENTER to shutdown system...\n";
    std::cin.get();

    running = false;

    for (auto& t : waiter_threads) {
        if (t.joinable()) t.join();
    }

    for (auto& t : chef_threads) {
        if (t.joinable()) t.join();
    }

    if (manager_thread.joinable()) manager_thread.join();
    if (dashboard_thread.joinable()) dashboard_thread.join();

    std::cout << "system shutdown complete\n";

    return 0;
}
