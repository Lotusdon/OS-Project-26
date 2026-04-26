#ifndef CHEF_H
#define CHEF_H

#include "OrderQueue.h"
#include <thread>
#include <atomic>
#include <semaphore>

extern std::atomic<bool> running;
extern std::counting_semaphore<10> stations;

class chef {
private:
    order_queue& queue;
    int chef_id;

public:
    chef(order_queue& q, int id);

    void run();
};

#endif
