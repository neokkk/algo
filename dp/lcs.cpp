#include <algorithm>
#include <string>
#include "dp.h"

void printLCSSubsequences(std::string a,
                          std::string b,
                          std::vector<std::vector<std::pair<int, int>>> found) {
    std::sort(found.begin(), found.end(), [](auto a, auto b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });
    found.erase(std::unique(found.begin(), found.end()), found.end());
    int prevSize = 0;
    for (auto subsequence : found) {
        if (subsequence.size() != prevSize) {
            prevSize = subsequence.size();
            PRINT("size: " << prevSize << std::endl);
        }
        std::string aSeq(a.size(), '_');
        std::string bSeq(b.size(), '_');
        for (auto pair : subsequence) {
            aSeq[pair.first] = a[pair.first];
            bSeq[pair.second] = b[pair.second];
        }
        PRINT("\t" << aSeq << " " << bSeq << std::endl);
    }
}

int LCSBruteForce(std::string a,
                  std::string b,
                  int i,
                  int j,
                  std::vector<std::pair<int, int>> subsequence,
                  std::vector<std::vector<std::pair<int, int>>>& found) {
    if (i >= a.size() || j >= b.size()) {
        found.push_back(subsequence);
        return subsequence.size();
    }

    if (a[i] == b[j]) {
        subsequence.push_back({i, j});
        return LCSBruteForce(a, b, i + 1, j + 1, subsequence, found);
    }

    return std::max(LCSBruteForce(a, b, i + 1, j, subsequence, found),
                    LCSBruteForce(a, b, i, j + 1, subsequence, found));
}

void runBruteForce() {
    std::vector<std::vector<std::pair<int, int>>> found;
    std::string a, b;
    std::cout << "input string a, b" << std::endl;
    std::cin >> a >> b;
    int lcs = LCSBruteForce(a, b, 0, 0, {}, found);
    std::cout << "LCS size: " << lcs << std::endl;
#ifdef DEBUG
    printLCSSubsequences(a, b, found);
#endif
}

int LCSMemoization(std::string a,
                   std::string b,
                   int i,
                   int j,
                   std::vector<std::vector<int>>& memo) {
    if (i == 0 || j == 0) return 0;
    if (memo[i - 1][j - 1] != -1) return memo[i - 1][j - 1];

    if (a[i - 1] == b[j - 1]) {
        memo[i - 1][j - 1] = 1 + LCSMemoization(a, b, i - 1, j - 1, memo);
        return memo[i - 1][j - 1];
    }

    memo[i - 1][j - 1] = std::max(LCSMemoization(a, b, i - 1, j, memo),
                                  LCSMemoization(a, b, i, j - 1, memo));

    return memo[i - 1][j - 1];
}

void runMemoization() {
    std::vector<std::tuple<std::string, std::string, int>> inputs{{"123456", "QWERTY", 0}, {"ACBEBC", "ABCBC", 4}, {"AZYBYXCXW", "ZZAYYBXXXCWW", 6}, {"ABCABDBEFBA", "ABCBEFBEAB", 8}, {"ABZCYDABAZADAEA", "YABAZADBBEAAECYACAZ", 10}};
    for (auto& tuple : inputs) {
        auto [a, b, result] = tuple;
        std::cout << a << ", " << b;
        std::vector<std::vector<int>> memo(a.size(), std::vector<int>(b.size(), -1));
        int lcs = LCSMemoization(a, b, a.size(), b.size(), memo);
        std::cout << ": " << lcs << std::endl;
        assert(lcs == result);
    }
}

std::string LCSTabulation(std::string a,
                          std::string b,
                          int i,
                          int j,
                          std::vector<std::vector<int>>& table) {
    if (i == 0 || j == 0) return "";
    else if (a[i - 1] == b[j - 1]) return LCSTabulation(a, b, i - 1, j - 1, table) + a[i - 1];
    else if (table[i - 1][j] > table[i][j - 1]) return LCSTabulation(a, b, i - 1, j, table);
    else return LCSTabulation(a, b, i, j - 1, table);
}

std::string getLCS(std::string a, std::string b) {
    std::vector<std::vector<int>> table(a.size() + 1, std::vector<int>(b.size() + 1));
    for (int i = 0; i <= a.size(); i++) {
        for (int j = 0; j <= b.size(); j++) {
            if (i == 0 || j == 0)
                table[i][j] = 0;
            else if (a[i - 1] == b[j - 1])
                table[i][j] = table[i - 1][j - 1] + 1;
            else
                table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
        }
    }
    std::string lcs = LCSTabulation(a, b, a.size(), b.size(), table);
    return lcs;
}

void runTabulation() {
    std::vector<std::tuple<std::string, std::string, std::string>> inputs{{"123456", "QWERTY", ""}, {"ACBEBC", "ABCBC", "ABBC"}, {"AZYBYXCXW", "ZZAYYBXXXCWW", "ZYYXXW"}, {"ABCABDBEFBA", "ABCBEFBEAB", "ABCBEFBA"}, {"ABZCYDABAZADAEA", "YABAZADBBEAAECYACAZ", "YABAZADAEA"}};
    for (const auto& input : inputs) {
        auto [a, b, result] = input;
        assert(getLCS(a, b) == result);
    }
}