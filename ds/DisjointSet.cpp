#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

class DisjointSet {
    class Unit {
    public:
        int id;
        Unit *parent;
        int rank;

        explicit Unit(int i): id{i}, parent{this}, rank{0} {}

        bool operator != (const Unit& u) const {
            return this->id != u.id;
        }
    };

    std::list<Unit *> set;

public:
    explicit DisjointSet(std::vector<int>& ids) {
        for (auto& id : ids)
            this->makeSet(id);
    }

    explicit DisjointSet(std::vector<int>&& ids) {
        for (int id : ids)
            this->makeSet(id);
    }

    virtual ~DisjointSet() {
        for (auto& s : set)
            delete s;
    }

    bool makeSet(int id) {
        auto it = std::find_if(this->set.begin(), this->set.end(), [&id](auto& u) {
            return id == u->id;
        });
        if (it != this->set.end()) return false;
        Unit *newUnit = new Unit{id};
        this->set.push_back(newUnit);
        return true;
    }

    static Unit *findRoot(Unit *unit) {
        Unit *current = unit;
        while (current->parent != current) {
            current = unit->parent;
        }
        return current;
    }

    Unit *unify(int x, int y) {
        auto xIt = std::find_if(this->set.begin(), this->set.end(), [&x](auto& u) {
            return x == u->id;
        });
        auto yIt = std::find_if(this->set.begin(), this->set.end(), [&y](auto& u) {
            return y == u->id;
        });

        if (xIt == this->set.end() || yIt == this->set.end()) return nullptr;
        return this->unify(*xIt, *yIt);
    }

    Unit *unify(Unit *x, Unit *y) { // union
        Unit *xRoot = this->findRoot(x);
        Unit *yRoot = this->findRoot(y);

        if (xRoot == yRoot) return nullptr; // 사이클 발생

        if (xRoot->rank > yRoot->rank)
            std::swap(xRoot, yRoot);

        yRoot->rank += 1;
        xRoot->parent = yRoot->parent;
        return xRoot;
    }

    static void print(Unit *unit) {
        if (unit == nullptr) return;
        Unit *current = unit;
        while (current->parent != current) {
            std::cout << current->id << "(" << current->rank << ") -> ";
            current = current->parent;
        }
        std::cout << current->id << "(" << current->rank << ")";
        std::cout << std::endl;
    }
};

void runDisjointSet() {
    std::vector<int> ids{1, 2, 3, 4, 5};
    auto ds = std::make_unique<DisjointSet>(ids);
    ds->print(ds->unify(1, 2));
    ds->print(ds->unify(5, 4));
}