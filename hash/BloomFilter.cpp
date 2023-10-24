//
// Created by nk on 2023/10/24.
//

#include <iostream>
#include <memory>
#include <vector>

int modulo(int n, int p) {
    return n % p;
}

class BloomFilter {
    std::vector<bool> data;
    int bits;

public:
    BloomFilter(int n): bits{n} {
        data = std::vector<bool>(n, false);
    }

    bool lookup(int key) {
        bool result = this->data[this->hash(0, key)]
                      & this->data[this->hash(1, key)]
                      & this->data[this->hash(2, key)];

        std::cout << key << ": ";
        if (result) std::cout << "있을 수 있다." << std::endl;
        else std::cout << "없다." << std::endl;

        return result;
    }

    void insert(int key) {
        this->data[this->hash(0, key)] = true;
        this->data[this->hash(1, key)] = true;
        this->data[this->hash(2, key)] = true;

        std::cout << "[";
        for (auto v : this->data)
            std::cout << " " << v << " ";
        std::cout << "]";
    }

private:
    int hash(int num, int key) {
        switch (num) {
            case 0: return modulo(key, this->bits);
            case 1: return modulo(key / 79, this->bits);
            case 2: return modulo(key / 311, this->bits);
            default: return -1;
        }
    }
};

void runBloomFilter() {
    auto bf = std::make_unique<BloomFilter>(100);
    bf->insert(4009);
    bf->insert(72);
    bf->insert(5);
    bf->insert(388);
    bf->insert(87);
    bf->lookup(4009);
    bf->lookup(1);
    bf->lookup(72);
    bf->lookup(10);
    bf->lookup(5);
    bf->lookup(100);
}