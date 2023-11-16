#include <cassert>
#include <iostream>
#include <vector>

void acc(std::vector<int>& set, std::vector<int> subset, int index, std::vector<std::vector<int>>& subsets) {
    if (!subset.empty()) {
        if (subset.back() == set.size()) {
            subsets.push_back(subset);
            return;
        }
        if (subset.back() > set.size() || index >= set.size()) {
            return;
        }
    } else {
        subset.push_back(index);
    }

    for (int i = 1; i <= set[index]; i++) {
        if (index + i == set.size()) {
            subsets.push_back(subset);
            return;
        } else {
            subset.push_back(index + i);
            acc(set, subset, index + i, subsets);
            subset.pop_back();
        }
    }
}

int travelPath(int n, std::vector<int>& distance) {
    int result = 0;
    std::vector<std::vector<int>> subsets;

    acc(distance, {}, 0, subsets);

    for (auto& subset : subsets) {
        for (auto s : subset) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        ++result;
    }

    result %= 1000000007;
    std::cout << "result: " << result << std::endl;
    return result;
}

std::vector<int> generator(int n) {
    std::vector<int> distance(n);
    long long val = 1;

    for (int i = 0; i < n; i++) {
        val = (val * 1103515245 + 12345) / 65536;
        val %= 32768;
        distance[i] = ((val % 10000) % (n - i)) + 1;
    }
    return distance;
}

void testTravelPath() {
    std::vector<int> n{3, 6, 15, 40, 100};
    std::vector<std::vector<int>> distances{{1, 1, 1}, {1, 2, 3, 2, 2, 1}, {1, 2, 5, 3, 4, 2, 1, 3, 6, 1, 2, 1, 2, 2, 1}, {8, 5, 9, 9, 11, 3, 10, 9, 9, 5, 1, 6, 13, 3, 13, 9, 8, 5, 11, 8, 4, 5, 10, 3, 11, 4, 10, 4, 12, 11, 8, 9, 3, 7, 6, 4, 4, 3, 2, 1}, {39, 79, 34, 76, 12, 28, 51, 60, 53, 7, 30, 48, 45, 61, 66, 24, 50, 64, 18, 47, 7, 19, 16, 72, 8, 55, 72, 26, 43, 57, 45, 26, 68, 23, 52, 28, 35, 54, 2, 57, 29, 59, 6, 57, 45, 26, 68, 23, 52, 28, 35, 54, 2, 57, 29, 59, 6, 57, 8, 47, 6, 44, 43, 35, 50, 41, 45, 4, 43, 39, 44, 43, 42, 26, 40, 39, 32, 37, 31, 20, 9, 33, 30, 27, 30, 29, 28, 27, 26, 25, 24, 23, 22, 15, 20, 19, 18, 17, 1, 15, 14, 2, 12, 11, 1, 6, 8, 7, 6, 5, 4, 3, 2, 1}};
    std::vector<int> result{1, 9, 789, 47382972, 790903754};

    for (int i = 0; i < n.size(); i++)
        assert(travelPath(n[i], distances[i]) == result[i]);
}