#ifndef ALGO_GRAPH_H
#define ALGO_GRAPH_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <vector>

struct Edge {
    int src, dst, weight;

    Edge() = default;

    Edge(int _src, int _dst, int _weight): src{_src}, dst{_dst}, weight{_weight} {}

    void print() {
        std::cout << this->src << " -> " << this->dst << "(" << this->weight << ")" << std::endl;
    }

    bool operator == (const Edge& rhs) const {
        return this->src == rhs.src && this->dst == rhs.dst;
    }

    bool operator > (const Edge& rhs) const {
        return this->weight > rhs.weight;
    }

    bool operator < (const Edge& rhs) const {
        return this->weight < rhs.weight;
    }
};

struct GraphWithList {
    GraphWithList() = default;

    int vertices() const;
    void addEdge(int src, int dst, int weight = 0, bool useWeight = false);
    void removeEdge(int src, int dst);
    const std::vector<Edge>& getEdges() const;
    std::vector<Edge> getEdges(int src) const;
    std::vector<int> getStartEdgeIds() const;
    void print() const;
    bool isExist(int src, int dst);

    private:
    int n = -1;
    std::vector<Edge> edges;
};

struct GraphWithMatrix {
    GraphWithMatrix(int _n);

    bool empty() const;
    int vertices() const;
    std::vector<int>& nonInDegrees();
    std::vector<std::vector<std::pair<int, int>>>& getEdges();
    void addEdge(int src, int dst, int weight);
    void removeEdge(int src, int dst);
    void removeEdges(int src);
    void print();

    private:
    int n;
    std::vector<std::vector<std::pair<int, int>>> edges;
    void dfs(std::vector<int>& visited, int index, int count, int limit);
};

#endif //ALGO_GRAPH_H
