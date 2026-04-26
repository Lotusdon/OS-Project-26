#ifndef WAITER_H
#define WAITER_H

#include "OrderQueue.h"
#include <thread>
#include <atomic>

extern std::atomic<bool> running;

class waiter {
private:
    order_queue& queue;
    int waiter_id;

public:
    waiter(order_queue& q, int id);

    void run();
};

#endif
