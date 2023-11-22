#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int knapsackTabulation(std::vector<int>& values,
                       std::vector<int>& weights,
                       int num,
                       int capacity,
                       std::vector<std::vector<int>>& selectedItems) {
    std::vector<std::vector<int>> table(num + 1, std::vector<int>(capacity + 1, 0));
    selectedItems.assign(num + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= num; i++) {
        int currentValue = values[i - 1];
        int currentWeight = weights[i - 1];
        for (int totalWeight = 1; totalWeight <= capacity; totalWeight++) {
            if (totalWeight < currentWeight) {
                table[i][totalWeight] = table[i - 1][totalWeight];
                selectedItems[i][totalWeight] = selectedItems[i - 1][totalWeight];
            }
            else {
                int withoutCurrent = table[i - 1][totalWeight];
                int withCurrent = table[i - 1][totalWeight - currentWeight] + currentValue;

                if (withCurrent > withoutCurrent) {
                    table[i][totalWeight] = withCurrent;
                    selectedItems[i][totalWeight] = 1; // 선택한 물건을 표시
                } else {
                    table[i][totalWeight] = withoutCurrent;
                    selectedItems[i][totalWeight] = selectedItems[i - 1][totalWeight];
                }
            }
        }
    }
    return table[num][capacity];
}

void printSelectedItems(const std::vector<std::vector<int>>& selectedItems,
                        const std::vector<int>& values,
                        const std::vector<int>& weights,
                        int num,
                        int capacity) {
    std::cout << "Selected items: ";
    int i = num;
    int w = capacity;
    while (i > 0 && w > 0) {
        if (selectedItems[i][w] == 1) {
            std::cout << values[i] << " ";
            w -= weights[i - 1];
        }
        i--;
    }
    std::cout << std::endl;
}

void runKnapsack() {
    int num = 8, capacity = 66;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> values, weights;
//    std::vector<int> values{20, 4, 89, 12, 5, 50, 8, 13}, weights{5, 23, 9, 72, 16, 14, 32, 4};
    std::vector<std::vector<int>> selectedItems;
    std::uniform_int_distribution<int> dis(1, 99);

    std::cout << "items num: " << std::endl;
    std::cin >> num;
    std::cout << "capacity: " << std::endl;
    std::cin >> capacity;

    values.assign(num, 0);
    weights.assign(num, 0);

    std::for_each(values.begin(), values.end(), [&](auto& v) {
        v = dis(gen);
    });
    for (auto v : values)
        std::cout << v << " ";
    std::cout << std::endl;
    std::for_each(weights.begin(), weights.end(), [&](auto& w) {
        w = dis(gen);
    });
    for (auto w : weights)
        std::cout << w << " ";
    std::cout << std::endl;

    int maxWeight = knapsackTabulation(values, weights, num, capacity, selectedItems);
    std::cout << "Max weight: " << maxWeight << std::endl;
    printSelectedItems(selectedItems, values, weights, num, capacity);
}