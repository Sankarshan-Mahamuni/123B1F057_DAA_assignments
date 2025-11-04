// Name: Sankarshan Satish Mahamuni
// PRN : 123B1F057

/*
Scenario:
A logistics company, SwiftCargo, specializes in delivering packages across multiple cities.
To optimize its delivery process, the company divides the transportation network into
multiple stages (warehouses, transit hubs, and final delivery points). Each package must
follow the most cost-efficient or fastest route from the source to the destination while
passing through these predefined stages.
As a logistics optimization engineer, you must:
1. Model the transportation network as a directed, weighted multistage graph with
multiple intermediate stages.
2. Implement an efficient algorithm (such as Dynamic Programming or Dijkstra’s
Algorithm) to find the optimal delivery route.
3. Ensure that the algorithm scales for large datasets (handling thousands of cities and
routes).

T.Y. B.Tech Information Technology, PCCoE Pune Page 10
4. Analyze and optimize route selection based on real-time constraints, such as traffic
conditions, weather delays, or fuel efficiency.
Constraints & Considerations:
● The network is structured into N stages, and every package must pass through at least
one node in each stage.
● There may be multiple paths with different costs/times between stages.
● The algorithm should be flexible enough to handle real-time changes (e.g., road
closures or rerouting requirements).
● The system should support batch processing for multiple delivery requests.
*/


#include <bits/stdc++.h>
using namespace std;

// ------------------- Edge Class -------------------
class Edge {
public:
    int to;      // destination node
    int cost;    // cost or travel time

    Edge(int to, int cost) {
        this->to = to;
        this->cost = cost;
    }
};

// ------------------- LogisticsOptimizer Class -------------------
class LogisticsOptimizer {
private:
    vector<vector<Edge>> graph;
    int N; // number of nodes

public:
    LogisticsOptimizer(int nodes) {
        N = nodes;
        graph.resize(N);
    }

    // Add a directed edge
    void addEdge(int from, int to, int cost) {
        graph[from].push_back(Edge(to, cost));
    }

    // Dynamic Programming to find shortest path in multistage graph
    vector<int> findShortestPath(int source, int destination) {
        vector<int> dist(N, INT_MAX);
        vector<int> nextNode(N, -1);

        dist[destination] = 0; // cost to reach destination from itself = 0

        // Go from second last node backward
        for (int i = N - 2; i >= 0; i--) {
            for (const auto &e : graph[i]) {
                if (dist[e.to] != INT_MAX && e.cost + dist[e.to] < dist[i]) {
                    dist[i] = e.cost + dist[e.to];
                    nextNode[i] = e.to;
                }
            }
        }

        return nextNode;
    }

    // Print the optimal path
    void printPath(int source, const vector<int> &nextNode) {
        int node = source;
        cout << node;
        while (nextNode[node] != -1) {
            node = nextNode[node];
            cout << " -> " << node;
        }
        cout << "\n";
    }
};

// ------------------- Main Function -------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, E;
    cout << "Enter number of nodes in multistage graph: ";
    cin >> N;

    LogisticsOptimizer system(N);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges as: from to cost\n";
    for (int i = 0; i < E; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        system.addEdge(u, v, cost);
    }

    int source, destination;
    cout << "Enter source node: ";
    cin >> source;
    cout << "Enter destination node: ";
    cin >> destination;

    auto startTime = chrono::high_resolution_clock::now();
    vector<int> nextNode = system.findShortestPath(source, destination);
    auto endTime = chrono::high_resolution_clock::now();

    cout << "\n--- Optimal Delivery Route ---\n";
    cout << "Path: ";
    system.printPath(source, nextNode);

    double duration = chrono::duration<double, milli>(endTime - startTime).count();
    cout << fixed << setprecision(3);
    cout << "Execution time: " << duration << " ms\n";

    return 0;
}
