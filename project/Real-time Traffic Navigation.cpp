#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// A structure to represent an edge in the graph
struct Edge {
    int destination, weight;
};

// Graph representation using an adjacency list
class Graph {
    int vertices;
    vector<vector<Edge>> adjList;

public:
    Graph(int v) : vertices(v), adjList(v) {}

    // Add an edge to the graph
    void addEdge(int source, int destination, int weight) {
        adjList[source].push_back({destination, weight});
        adjList[destination].push_back({source, weight}); // For an undirected graph
    }

    // Dijkstra's algorithm to find shortest paths
    void dijkstra(int start) {
        vector<int> distances(vertices, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int current = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            // Skip outdated distance entries
            if (currentDistance > distances[current])
                continue;

            for (const auto &edge : adjList[current]) {
                int neighbor = edge.destination;
                int weight = edge.weight;

                // Relaxation step
                if (distances[current] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[current] + weight;
                    pq.push({distances[neighbor], neighbor});
                }
            }
        }

        // Output shortest distances
        for (int i = 0; i < vertices; ++i) {
            cout << "Shortest distance from " << start << " to " << i << ": ";
            if (distances[i] == INT_MAX)
                cout << "INF" << endl;
            else
                cout << distances[i] << endl;
        }
    }
};

// Main function
int main() {
    int vertices = 5;
    Graph graph(vertices);

    // Adding edges: source, destination, weight
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(3, 4, 3);

    int startNode = 0;
    cout << "Real-time Traffic Navigation using Dijkstra's Algorithm:\n";
    graph.dijkstra(startNode);

    return 0;
}
