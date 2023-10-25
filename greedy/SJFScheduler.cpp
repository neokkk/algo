//
// Created by nk on 2023/10/25.
//

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

class SJFScheduler {
    std::vector<std::array<int, 3>> jobs; // {idx, service time, wait time}

public:
    SJFScheduler(std::vector<int>& serviceTimes) {
        jobs = std::vector<std::array<int, 3>>(serviceTimes.size());

        for (int idx = 0; auto& s : serviceTimes) {
            jobs[idx][0] = idx;
            jobs[idx][1] = s;
            ++idx;
        }

        // sort by shortest job finishing
        std::sort(jobs.begin(), jobs.end(), [](auto& t1, auto& t2) {
            return t1[1] < t2[1];
        });

        // accumulate each jobs waiting
        for (int i = 1; i < jobs.size(); i++) {
            jobs[i][2] = jobs[i - 1][1] + jobs[i - 1][2];
        }
    }

    virtual ~SJFScheduler() = default;

    int getAvgWaitingTime() {
        return this->jobs.back()[2];
    }

    std::vector<int> getOrder() {
        std::vector<int> order(this->jobs.size());
        std::transform(this->jobs.begin(), this->jobs.end(), order.begin(), [](auto& j) {
            return j[0];
        });
        return std::move(order);
    }

    void print() {
        for (auto& j : this->jobs) {
            std::cout << "[" << j[0] << "] " << j[1] << "(" << j[2] << ")" << std::endl;
        }
    }
};

void runSJFScheduler() {
    std::vector<int> serviceTimes{8, 1, 2, 4, 9, 2, 3, 5};
    auto scheduler = std::make_unique<SJFScheduler>(serviceTimes);
    scheduler->print();
    std::cout << "average waiting time: " << scheduler->getAvgWaitingTime() << std::endl;
    std::vector<int> order = scheduler->getOrder();
    std::cout << "order: ";
    for (auto& o : order)
        std::cout << o << " ";
    std::cout << std::endl;
}