#include <iostream>
#include <queue>
#include <unordered_set>
#include "../ds/Graph.cpp"

void bfs(const GraphWithList& graph, int start) {
    std::queue<Edge> q;
    std::unordered_set<int> visited;
    std::vector<int> order;

    visited.insert(start);
    order.push_back(start);

    for (auto& edge : graph.getEdges(start)) {
        q.push(edge);
    }

    while (!q.empty()) {
        Edge cur = q.front();
        q.pop();

        if (visited.find(cur.dst) == visited.end()) {
            visited.insert(cur.dst);
            order.push_back(cur.dst);
        }

        for (const Edge& edge : graph.getEdges(cur.dst)) {
            if (visited.find(edge.dst) == visited.end())
                q.push(edge);
        }
    }

    for (auto& o : order)
        std::cout << o << " -> ";
    std::cout << std::endl;
}

void runBFS() {
    GraphWithList g(8);
    g.addEdge(1, 2);
    g.addEdge(1, 5);
    g.addEdge(2, 1);
    g.addEdge(2, 5);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 7);
    g.addEdge(4, 2);
    g.addEdge(4, 3);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(4, 8);
    g.addEdge(5, 1);
    g.addEdge(5, 2);
    g.addEdge(5, 4);
    g.addEdge(5, 8);
    g.addEdge(6, 4);
    g.addEdge(6, 7);
    g.addEdge(6, 8);
    g.addEdge(7, 3);
    g.addEdge(7, 6);
    g.addEdge(8, 4);
    g.addEdge(8, 5);
    g.addEdge(8, 6);
    bfs(g, 1);
}