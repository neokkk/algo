#include <queue>
#include "../ds/DisjointSet.cpp"
#include "../ds/Graph.cpp"

std::vector<Edge> kruskal(GraphWithList& graph) {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<>> minHeap;
    auto edges = graph.getEdges();
    std::vector<Edge> order;

    for (auto& edge : edges)
        minHeap.push(edge);

    DisjointSet dset{graph.getStartEdgeIds()};

    while (!minHeap.empty()) {
        auto current = minHeap.top();
        if (dset.unify(current.src, current.dst) != nullptr) {
            std::cout << current.src << " -> " << current.dst << "(" << current.weight << ")" << std::endl;
            order.push_back(current);
        }
        minHeap.pop();
    }

    return order;
}

void runKruskal() {
    GraphWithList g{9};
    g.addEdge(1, 2, 2, true);
    g.addEdge(1, 5, 3, true);
    g.addEdge(2, 1, 2, true);
    g.addEdge(2, 5, 5, true);
    g.addEdge(2, 4, 1, true);
    g.addEdge(3, 4, 2, true);
    g.addEdge(3, 7, 3, true);
    g.addEdge(3, 7, 3, true);
    g.addEdge(4, 2, 1, true);
    g.addEdge(4, 3, 2, true);
    g.addEdge(4, 5, 2, true);
    g.addEdge(4, 6, 4, true);
    g.addEdge(4, 8, 5, true);
    g.addEdge(5, 1, 3, true);
    g.addEdge(5, 2, 5, true);
    g.addEdge(5, 4, 2, true);
    g.addEdge(5, 8, 3, true);
    g.addEdge(6, 4, 4, true);
    g.addEdge(6, 8, 1, true);
    g.addEdge(7, 3, 3, true);
    g.addEdge(7, 6, 4, true);
    g.addEdge(8, 4, 5, true);
    g.addEdge(8, 5, 3, true);
    g.addEdge(8, 6, 1, true);
    g.print();
    std::vector<Edge> order = kruskal(g);
    for (auto& e : order) {
        e.print();
    }
}