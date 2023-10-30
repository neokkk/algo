#include <algorithm>
#include <fstream>
#include <sstream>
#include "mst.cpp"

std::vector<int> dijkstra(GraphWithList& graph, int src, int dst) {
    std::priority_queue<Label, std::vector<Label>, std::greater<>> minHeap;
    std::unordered_map<int, int> distances;
    std::unordered_map<int, int> order;
    std::unordered_set<int> visited;

    for (auto& id : graph.getStartEdgeIds())
        distances.insert(std::make_pair<>(id, std::numeric_limits<int>::max()));

    minHeap.emplace(src, 0);

    while (!minHeap.empty()) {
        auto currentLabel = minHeap.top();
        minHeap.pop();

        if (currentLabel.id == dst) {
            std::cout << currentLabel.id << "번 노드에 도착!" << std::endl;
            break;
        }

        if (visited.find(currentLabel.id) == visited.end()) {
            visited.insert(currentLabel.id);

            for (auto& edge : graph.getEdges(currentLabel.id)) {
                auto distance = distances.at(edge.dst);
                int newDistance = currentLabel.distance + edge.weight;
                if (newDistance < distance) {
                    distances.at(edge.dst) = newDistance;
                    minHeap.emplace(edge.dst, newDistance);
                    order.insert(std::make_pair<>(edge.dst, currentLabel.id));
                }
            }
        }
    }

    /* backtracking */
    std::vector<int> shortest;
    auto currentNode = dst;

    while (currentNode != src) {
        shortest.push_back(currentNode);
        currentNode = order.at(currentNode);
    }

    shortest.push_back(src);
    std::reverse(shortest.begin(), shortest.end());

    return std::move(shortest);
}

void runDijkstra() {
    GraphWithList g;
    g.addEdge(1, 2, 2);
    g.addEdge(1, 5, 3);
    g.addEdge(2, 1, 2);
    g.addEdge(2, 5, 5);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 7, 3);
    g.addEdge(3, 7, 3);
    g.addEdge(4, 2, 1);
    g.addEdge(4, 3, 2);
    g.addEdge(4, 5, 2);
    g.addEdge(4, 6, 4);
    g.addEdge(4, 8, 5);
    g.addEdge(5, 1, 3);
    g.addEdge(5, 2, 5);
    g.addEdge(5, 4, 2);
    g.addEdge(5, 8, 3);
    g.addEdge(6, 4, 4);
    g.addEdge(6, 8, 1);
    g.addEdge(7, 3, 3);
    g.addEdge(7, 6, 4);
    g.addEdge(8, 4, 5);
    g.addEdge(8, 5, 3);
    g.addEdge(8, 6, 1);
    g.print();
    auto order = dijkstra(g, 1, 6);
    for (auto& e : order)
        std::cout << e << " ";
    std::cout << std::endl;
}

void runNYRoadShortestPath() {
    GraphWithList graph;

    std::ifstream file("algo/USA-road-d.NY.gr");
    if (!file.is_open()) {
        std::cerr << "fail to open file" << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0] != 'a') continue;
        std::istringstream iss(line);
        char a;
        int src, dst, weight;
        iss >> a >> src >> dst >> weight;
        std::cout << src << ", " << dst << std::endl;
        graph.addEdge(src, dst, weight);
    }

    file.close();
    dijkstra(graph, 913, 542);
}