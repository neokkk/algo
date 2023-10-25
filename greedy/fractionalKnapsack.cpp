//
// Created by nk on 2023/10/25.
//

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class Object {
public:
    static int idgen;
    int id;
    double weight;
    double value;
    double vpw; // value per weight

    Object(double w, double v): id{idgen++}, weight{w}, value{v}, vpw{value / weight} {}

    virtual ~Object() = default;

    friend std::ostream& operator << (std::ostream& os, const Object& obj) {
        os << "[" << obj.id << "] " << obj.weight << " (" << obj.value << ", " << obj.vpw << ")" << std::endl;
        return os;
    }
};

int Object::idgen = 0;

bool operator > (const Object& lhs, const Object& rhs) {
    return lhs.vpw > rhs.vpw;
}

double operator + (const Object& lhs, const Object& rhs) {
    return lhs.value + rhs.value;
}

double operator + (double v, const Object& obj) {
    return v + obj.value;
}

std::vector<Object> fillKnapsack(std::vector<Object>& objects, double capacity) {
    std::vector<Object> contained;
    auto iter = objects.begin();

    std::sort(objects.begin(), objects.end(), [](auto& lhs, auto& rhs) {
        return lhs > rhs;
    });

    std::cout << "[sorted]" << std::endl;
    for (auto& o : objects) {
        std::cout << o;
    }

    while (iter < objects.end()) {
        if (capacity <= (*iter).weight) {
            double fraction = capacity / (*iter).weight;
            Object fractionalObject(fraction * (*iter).weight, fraction * (*iter).value);
            contained.push_back(fractionalObject);
            break;
        } else {
            capacity -= (*iter).weight;
            contained.push_back(*iter);
        }
        iter++;
    }

    return contained;
}

void runFractionalKnapsack() {
    int capacity = 7;
    std::vector<Object> objects{{1, 10}, {2, 7}, {5, 15}, {9, 10}, {2, 12}, {3, 11}, {4, 5}};
    std::vector<Object> contained = fillKnapsack(objects, capacity);

    std::cout << std::endl;
    std::cout << "[contained (~" << capacity << ")]" << std::endl;
    for (auto& o : contained) {
        std::cout << o;
    }
    auto acc = std::accumulate(contained.begin(), contained.end(), 0.0);
    std::cout << "acc value: " << acc << std::endl;
}