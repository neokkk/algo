#include "dp.h"

void getAllSubsets(std::vector<int> set,
                   std::vector<int> subset,
                   int index,
                   std::vector<std::vector<std::vector<int>>>& allSubsets) {
if (index == set.size()) {
allSubsets[subset.size()].push_back(subset);
return;
}

// 원소를 부분집합에 추가 x
getAllSubsets(set, subset, index + 1, allSubsets);

// 원소를 부분집합에 추가
subset.push_back(set[index]);
getAllSubsets(set, subset, index + 1, allSubsets);
}

bool sumSubsetBruteForce(std::vector<int>& set, int target) {
    std::vector<std::vector<std::vector<int>>> allSubsets(set.size() + 1);
    getAllSubsets(set, {}, 0, allSubsets);

    for (int i = 0; i <= set.size(); i++) {
        PRINT("subset size: " << i << std::endl);
        for (auto subset : allSubsets[i]) {
            PRINT("\t{ ");
            int sum = 0;
            for (auto n : subset) {
                sum += n;
                PRINT(n << " ");
            }
            PRINT("} = " << sum << std::endl);
            if (sum == target)
                return true;
        }
    }
    return false;
}

void runBruteForce() {
    std::vector<int> set{16, 1058, 22, 13, 46, 55, 3, 92, 47, 7, 98, 367, 807, 106, 333, 85, 577, 9, 3059};
    int target = 6099;

    auto start = std::chrono::high_resolution_clock::now();
    bool found = sumSubsetBruteForce(set, target);
    auto end = std::chrono::high_resolution_clock::now();

    if (found)
        std::cout << "[bruteforce] has subset" << std::endl;
    else
        std::cout << "[bruteforce] has no subset" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << "s" << std::endl;
}

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