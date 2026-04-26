#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "OrderQueue.h"
#include <atomic>
#include <thread>

extern std::atomic<bool> running;

struct stats {
    std::atomic<int> total_orders{0};
    std::atomic<int> completed_orders{0};
    std::atomic<int> cancelled_orders{0};
};

class dashboard {
private:
    order_queue& queue;
    stats& system_stats;

public:
    dashboard(order_queue& q, stats& s);

    void run();
};

#endif
