// Name: Sankarshan Satish Mahamuni
// PRN : 123B1F057


/*
Scenario: Smart Traffic Management for Emergency Vehicles
A smart city is implementing an intelligent traffic management system to assist ambulances
in reaching hospitals as quickly as possible. The city’s road network is represented as a
graph, where:
● Intersections (junctions) are nodes.
● Roads between intersections are edges with weights representing travel time (in minutes)
considering traffic congestion.
An ambulance is currently at Source (S) and needs to reach the nearest hospital (Destination
D) in the shortest possible time. Due to dynamic traffic conditions, the weight of each road
segment may change in real time.
As a transportation engineer, you are assigned to:
1. Implement Dijkstra’s algorithm to find the shortest path from the ambulance's current
location (S) to all possible hospitals.
2. Account for dynamic weight updates as traffic conditions change.
3. Optimize the system to work efficiently for a large city with thousands of intersections
and roads.
4. Provide a visual representation of the optimal path for navigation.
Expected Outcome:
The system should suggest the quickest route for the ambulance, updating dynamically
based on real-time traffic conditions, ensuring minimal response time to emergencies.
*/
#include <bits/stdc++.h>
using namespace std;

class Road {
public:
    int destination;
    int travelTime; // in minutes

    Road(int destination, int travelTime) {
        this->destination = destination;
        this->travelTime = travelTime;
    }
};


class TrafficSystem {
private:
    vector<vector<Road>> graph;
    int numIntersections;

public:
    TrafficSystem(int n) {
        numIntersections = n;
        graph.resize(n);
    }

    void addRoad(int u, int v, int t) {
        graph[u].push_back(Road(v, t));
        graph[v].push_back(Road(u, t));
    }

  
    vector<int> dijkstra(int start, vector<int>& previousNode) {
        int n = numIntersections;
        vector<int> travelTime(n, INT_MAX);
        previousNode.assign(n, -1);
        travelTime[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();

            if (time > travelTime[node])
                continue;

            for (const auto& road : graph[node]) {
                int neighbor = road.destination;
                int newTime = travelTime[node] + road.travelTime;

                if (newTime < travelTime[neighbor]) {
                    travelTime[neighbor] = newTime;
                    previousNode[neighbor] = node;
                    pq.push({newTime, neighbor});
                }
            }
        }

        return travelTime;
    }


    void printPath(const vector<int>& previousNode, int destination) {
        if (previousNode[destination] == -1) {
            cout << destination;
            return;
        }
        printPath(previousNode, previousNode[destination]);
        cout << " -> " << destination;
    }

    int findNearestHospital(const vector<int>& travelTime, const vector<int>& hospitals) {
        int nearest = -1, minTime = INT_MAX;
        for (int h : hospitals) {
            if (travelTime[h] < minTime) {
                minTime = travelTime[h];
                nearest = h;
            }
        }
        return nearest;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numIntersections, numRoads;
    cout << "Number of intersections: ";
    cin >> numIntersections;
    cout << "Number of roads: ";
    cin >> numRoads;

    TrafficSystem system(numIntersections);

    cout << "Enter roads as: start end travelTime\n";
    for (int i = 0; i < numRoads; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        system.addRoad(u, v, t);
    }

    int start;
    cout << "Ambulance starts at intersection: ";
    cin >> start;

    int numHospitals;
    cout << "Number of hospitals: ";
    cin >> numHospitals;
    vector<int> hospitals(numHospitals);
    cout << "Enter hospital nodes: ";
    for (int i = 0; i < numHospitals; i++)
        cin >> hospitals[i];

    vector<int> previousNode;
    cout << "\nCalculating shortest paths...\n";
    auto startTime = chrono::high_resolution_clock::now();

    vector<int> travelTime = system.dijkstra(start, previousNode);

    auto endTime = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, milli>(endTime - startTime).count();

    int nearestHospital = system.findNearestHospital(travelTime, hospitals);

    cout << "\n--- Emergency Route ---\n";
    cout << "Ambulance start: " << start << "\n";
    cout << "Hospitals: ";
    for (int h : hospitals) cout << h << " ";
    cout << "\n";

    if (nearestHospital == -1 || travelTime[nearestHospital] == INT_MAX) {
        cout << "No reachable hospital!\n";
    } else {
        cout << "Nearest hospital: " << nearestHospital
             << " (time: " << travelTime[nearestHospital] << " mins)\n";
        cout << "Shortest path: ";
        system.printPath(previousNode, nearestHospital);
        cout << "\n";
    }

    cout << fixed << setprecision(3);
    cout << "Execution time: " << duration << " ms\n";

    return 0;
}

