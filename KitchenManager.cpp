#include "KitchenManager.h"
#include <iostream>
#include <chrono>
#include <thread>

extern std::counting_semaphore<10> stations;

kitchen_manager::kitchen_manager(order_queue& q)
    : queue(q), max_stations(3), active_adjustment(0) {}

void kitchen_manager::run() {

    while (running) {

        int qsize = queue.size();
        int current = max_stations.load();

        if (qsize > 10 && current < 6) {
        
            max_stations++;
        
            stations.release();
        
            std::cout << "manager: increasing stations to " << max_stations.load() << "\n";
        }
        else if (qsize < 3 && current > 2) {
        
            max_stations--;
        
            stations.acquire();
        
            std::cout << "manager: decreasing stations to " << max_stations.load() << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int kitchen_manager::get_max_stations() {
    return max_stations.load();
}
