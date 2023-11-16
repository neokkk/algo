#include "dp.h"

std::vector<std::vector<bool>> sumSubsetTabulation(std::vector<int>& set) {
    int maxSum = std::accumulate(set.begin(), set.end(), 0);
    std::vector<std::vector<bool>> table(set.size() + 1, std::vector<bool>(maxSum + 1, false));
    for (int i = 0; i < set.size(); i++) {
        table[i][0] = true;
    }
    for (int i = 1; i <= set.size(); i++) {
        for (int sum = 1; sum <= maxSum; sum++) {
            if (sum < set[i - 1])
                table[i][sum] = table[i - 1][sum];
            else
                table[i][sum] = table[i - 1][sum] || table[i - 1][sum - set[i - 1]];
        }
    }
    return std::move(table);
}

std::vector<int> getAllSubsetSums(std::vector<int>& set, std::vector<std::vector<bool>>& table) {
    int total = std::accumulate(set.begin(), set.end(), 0);
    std::vector<int> subsetSums;
    for (int sum = 1; sum <= total; sum++) {
        if (table[set.size()][sum])
            subsetSums.push_back(sum);
    }
    return std::move(subsetSums);
}

void runTabulation() {
    std::vector<int> set{16, 1058, 22, 13, 46, 55, 3, 92, 47, 7, 98, 367, 807, 106, 333, 85, 577, 9, 3059};
    int target = 6099;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<bool>> table = sumSubsetTabulation(set);
    auto found = table[set.size()][target];
    auto end = std::chrono::high_resolution_clock::now();
    auto subsetSums = getAllSubsetSums(set, table);

    if (found)
        std::cout << "[tabulation] has " << subsetSums.size() << " subset" << std::endl;
    else
        std::cout << "[tabulation] has no subset" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << "s" << std::endl;
}