#include "dp.h"
#include "../util.h"

template <typename T>
void combinationBruteForce(std::vector<T>& vec,
                           std::vector<T> subset,
                           int index,
                           std::vector<std::vector<T>>& subsets) {
    if (index == vec.size()) {
        subsets.push_back(subset);
        return;
    }
    combination(vec, subset, index + 1, subsets);
    subset.push_back(vec[index]);
    combination(vec, subset, index + 1, subsets);
}

template <typename T>
std::vector<std::vector<T>> combinationTabulation(std::vector<T>& vec, int select) {
    std::vector<std::vector<T>> result;

    if (select == 1) {
        for (const auto& v : vec) {
            result.push_back({v});
        }
        return result;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        auto fixed = vec[i];
        std::vector<int> rest(vec.begin() + i + 1, vec.end());

        auto picked = combinationTabulation(rest, select - 1);

        for (const auto& v : picked) {
            std::vector attached = {fixed};
            attached.insert(attached.end(), v.begin(), v.end());
            result.push_back(attached);
        }
    }

    return result;
}

void runStringCombination() {
    std::string word{"ABCDEFG"};
    std::vector<char> wordVec(word.begin(), word.end());
    std::vector<std::vector<char>> subsets;

//    combinationBruteForce(wordVec, {}, 0, subsets);
    subsets = combinationTabulation(wordVec, 3);

    for (auto& subset : subsets) {
        std::cout << std::string(subset.begin(), subset.end()) << std::endl;
    }
}