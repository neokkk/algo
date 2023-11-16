#include "dp.h"

bool sumSubsetMemoization(std::vector<int>& set,
                          int sum,
                          int index,
                          std::vector<std::vector<int>>& memo) {
    if (sum == 0) return true;
    if (index == set.size() || set[index] > sum) return false;
    if (memo[index][sum] == UNKNOWN) {
        bool append = sumSubsetMemoization(set, sum - set[index], index + 1, memo);
        bool ignore = sumSubsetMemoization(set, sum, index + 1, memo);
        memo[index][sum] = append || ignore;
    }
    return memo[index][sum];
}

void runMemoization() {
    std::vector<int> set{16, 1058, 22, 13, 46, 55, 3, 92, 47, 7, 98, 367, 807, 106, 333, 85, 577, 9, 3059};
    std::vector<std::vector<int>> memo(set.size(), std::vector<int>(7000, UNKNOWN));
    int target = 6799;

    auto start = std::chrono::high_resolution_clock::now();
    bool found = sumSubsetMemoization(set, target, 0, memo);
    auto end = std::chrono::high_resolution_clock::now();

    if (found)
        std::cout << "[memoization] has subset" << std::endl;
    else
        std::cout << "[memoization] has no subset" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << "s" << std::endl;
}