#ifndef KITCHEN_MANAGER_H
#define KITCHEN_MANAGER_H

#include "OrderQueue.h"
#include <atomic>
#include <thread>

extern std::atomic<bool> running;

class kitchen_manager {
private:
    order_queue& queue;

    std::atomic<int> max_stations;
    std::atomic<int> active_adjustment;

public:
    kitchen_manager(order_queue& q);

    void run();

    int get_max_stations();
};

#endif
