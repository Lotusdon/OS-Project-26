#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <chrono>

enum class order_priority {
    normal,
    vip
};

enum class order_status {
    pending,
    in_progress,
    done,
    cancelled
};

struct order {
    int order_id;
    std::string customer_name;
    std::string item_name;
    int quantity;
    double price;

    order_priority priority;
    order_status status;

    std::chrono::steady_clock::time_point timestamp;
};

#endif
