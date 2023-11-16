#include "dp.h"

bool sumSubsetBackTracking(std::vector<int>& set, int sum, int index) {
    if (sum == 0) return true;
    if (index == set.size() || set[index] > sum) return false;
    bool append = sumSubsetBackTracking(set, sum - set[index], index + 1);
    bool ignore = sumSubsetBackTracking(set, sum, index + 1);
    return append || ignore;
}

void runBackTracking() {
    std::vector<int> set{16, 1058, 22, 13, 46, 55, 3, 92, 47, 7, 98, 367, 807, 106, 333, 85, 577, 9, 3059};
    int target = 6099;

    auto start = std::chrono::high_resolution_clock::now();
    bool found = sumSubsetBackTracking(set, target, 0);
    auto end = std::chrono::high_resolution_clock::now();

    if (found)
        std::cout << "[backtracking] has subset" << std::endl;
    else
        std::cout << "[backtracking] has no subset" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << "s" << std::endl;
}