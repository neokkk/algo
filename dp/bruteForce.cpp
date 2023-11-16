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
