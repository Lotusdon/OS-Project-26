#ifndef ORDER_QUEUE_H
#define ORDER_QUEUE_H

#include "Order.h"
#include <queue>
#include <mutex>
#include <condition_variable>

struct order_compare {
    bool operator()(const order& a, const order& b) const {
        if (a.priority != b.priority) {
            return a.priority < b.priority;
        }
        return a.timestamp > b.timestamp;
    }
};

class order_queue {
private:
    std::priority_queue<order, std::vector<order>, order_compare> pq;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(const order& o) {
        std::lock_guard<std::mutex> lock(mtx);
        pq.push(o);
        cv.notify_one();
    }

    bool try_pop(order& result) {
        std::lock_guard<std::mutex> lock(mtx);
        if (pq.empty()) return false;

        result = pq.top();
        pq.pop();
        return true;
    }

    order wait_and_pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return !pq.empty(); });

        order result = pq.top();
        pq.pop();
        return result;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return pq.empty();
    }

    int size() {
        std::lock_guard<std::mutex> lock(mtx);
        return pq.size();
    }

    void cancel_order(int id) {

        std::lock_guard<std::mutex> lock(mtx);

        std::vector<order> temp;

        while (!pq.empty()) {

            order o = pq.top();
            pq.pop();

            if (o.order_id != id) {
            temp.push_back(o);
            }
        }

    for (auto& o : temp) {
        pq.push(o);
    }
}
};

#endif
