#ifndef WAITER_H
#define WAITER_H

#include "OrderQueue.h"
#include "Dashboard.h"
#include <thread>
#include <atomic>

extern std::atomic<bool> running;

class waiter {
private:
    order_queue& queue;
    stats& system_stats;
    int waiter_id;

public:
    waiter(order_queue& q, stats& s, int id);

    void run();
};

#endif
