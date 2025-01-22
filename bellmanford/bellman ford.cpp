#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void bellman_ford(const vector<vector<pair<int, int>>>& graph, int source) {
    const int n = graph.size();
    const int INF = numeric_limits<int>::max();
    vector<int> D(n, INF); // Initialize distances to INF
    D[source] = 0;         // Distance to the source is 0

    // Relax edges (n-1) times
    for (int k = 0; k < n - 1; ++k) {
        bool updated = false; // Track if any distance was updated
        for (int u = 0; u < n; ++u) {
            if (D[u] == INF) continue; // Skip nodes not reachable yet
            for (auto& edge : graph[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (D[u] + weight < D[v]) {
                    D[v] = D[u] + weight;
                    updated = true; // Mark that an update occurred
                }
            }
        }
        if (!updated) break; // If no updates, terminate early
    }

    // Check for negative weight cycles
    for (int u = 0; u < n; ++u) {
        if (D[u] == INF) continue; // Skip nodes not reachable
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (D[u] + weight < D[v]) {
                cout << "Graph contains negative weight cycle" << endl;
                return;
            }
        }
    }

    // Print the distances
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << (D[i] == INF ? "INF" : to_string(D[i])) << endl;
    }
}

int main() {
    // Define the graph
    vector<vector<pair<int, int>>> graph = {
            {{1, 2}, {2, 3}},    // Node 0
            {{2, -1}, {3, 1}},   // Node 1
            {{3, 2}},            // Node
            {}                   // Node 3
    };

    int source_node;
    cout  << "ENTER THE SOURCE NODE: ";
    cin >> source_node; // Take the source node as input

    bellman_ford(graph, source_node);
    return 0;
}


