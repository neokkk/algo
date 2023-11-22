#include <algorithm>
#include <iostream>
#include <vector>

int cmm(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& opt) {
    int size = matrix.size();
    std::vector<std::vector<int>> table(size, std::vector<int>(size, 0));
    opt.assign(size - 1, std::vector<int>(size - 1, 0));

    for (int l = 1; l < size; l++) {
        for (int start = 0; start < size - l; start++) {
            int end = start + l;
            if (end >= size) break;
            table[start][end] = std::numeric_limits<int>::max();
            for (int k = start; k < end; k++) {
                int q = table[start][k] + table[k + 1][end] + matrix[start][0] * matrix[k + 1][0] * matrix[end][1];
                if (q < table[start][end]) {
                    table[start][end] = q;
                    opt[start][end] = k;
                }
            }
        }
    }

    return table[0][size - 1];
}

void printOptimalParens(std::vector<std::vector<int>>& parens, int i, int j) {
    if (i == j)
        std::cout << "M" << i;
    else {
        std::cout << "(";
        printOptimalParens(parens, i, parens[i][j]);
        printOptimalParens(parens, parens[i][j] + 1, j);
        std::cout << ")";
    }
}

void runCMM() {
    std::vector<std::tuple<std::vector<std::vector<int>>, int>> cases{
        {{{5, 3}, {3, 10}, {10, 6}}, 270},
        {{{10, 20}, {20, 30}, {30, 40}, {40, 30}}, 30000},
//        {{{5, 10}, {10, 3}, {3, 12}, {12, 5}}, 630},
        {{{4, 5}, {5, 10}, {10, 3}, {3, 12}}, 464},
    };
    for (auto& c : cases) {
        std::vector<std::vector<int>> optimal;
        auto [matrix, result] = c;
        std::cout << cmm(matrix, optimal);
//        assert(cmm(matrix, optimal) == result);
        for (const auto& r : optimal) {
            for (const auto& c : r) {
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }
        printOptimalParens(optimal, 0, matrix.size() - 1);
        std::cout << std::endl;
        std::cout << "------------" << std::endl;
    }
}