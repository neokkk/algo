#include "Graph.h"

int GraphWithList::verticies() const {
    return this->n;
}

void GraphWithList::addEdge(int src, int dst, int weight, bool useWeight) {
    if (!validate(src, dst)) return;
    if (this->isExist(src, dst)) return;
    this->edges.emplace_back(src, dst, weight);
    if (useWeight) this->edges.emplace_back(dst, src, weight);
}

void GraphWithList::removeEdge(int src, int dst) {
    if (!validate(src, dst)) return;
    auto edge = Edge{src, dst, 0};
    std::remove(this->edges.begin(), this->edges.end(), edge);
}

const std::vector<Edge>& GraphWithList::getEdges() const {
    return this->edges;
}

std::vector<Edge> GraphWithList::getEdges(int src) const {
    std::vector<Edge> tmp;

    for (auto& edge : this->edges) {
        if (edge.src == src)
            tmp.emplace_back(edge);
    }

    return std::move(tmp);
}

std::vector<int> GraphWithList::getStartEdgeIds() const {
    std::unordered_set<int> set;
    std::vector<int> tmp;

    for (auto& edge: this->edges)
        set.insert(edge.src);

    std::copy(set.begin(), set.end(), std::back_inserter(tmp));

    return std::move(tmp);
}

void GraphWithList::print() const {
    for (int i = 0; i < n; i++) {
        std::cout << "Node " << i;
        for (const auto& edge : getEdges(i))
            std::cout << " -> Node " << edge.dst << "(" << edge.weight << ")";
        std::cout << std::endl;
    }
}

bool GraphWithList::isExist(int src, int dst) {
    Edge tmp{src, dst, 0};
    return std::find(this->edges.begin(), this->edges.end(), tmp) != this->edges.end();
}

bool GraphWithList::validate(int src, int dst) {
    return (src >= 0 && src < n && dst >= 0 || dst < n);
}

GraphWithMatrix::GraphWithMatrix(int _n): n{_n} {
    edges.assign(n, std::vector<std::pair<int, int>>());
}

bool GraphWithMatrix::empty() const {
    return std::all_of(this->edges.begin(), this->edges.end(), [](const auto& edge) {
        return edge.size() == 0;
    });
}

int GraphWithMatrix::vertices() const {
    return n;
}

void GraphWithMatrix::addEdge(int src, int dst, int value) {
    this->edges.at(src).push_back(std::make_pair(dst, value));
}

void GraphWithMatrix::removeEdge(int src, int dst) {
    auto _edges = this->edges.at(src);
    std::remove_if(_edges.begin(), _edges.end(), [dst](const auto& e) {
        return e.first == dst;
    });
}

void GraphWithMatrix::removeEdges(int src) {
    this->edges.at(src).clear();
}
