//Eduardo Avila
//COMSC - 210 - 5293
//Lab 34 - Network Graph 1

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;
    vector<string> locationNames;

    // Build the graph and store the location names
    Graph(vector<Edge> const &edges, vector<string> const &names) {
        adjList.resize(SIZE);
        locationNames = names;

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // Add the road in both directions
            adjList[src].push_back({dest, weight});
            adjList[dest].push_back({src, weight});
        }
    }

    // Display the city road network
    void printGraph() {
        cout << "City Road Network Topology:" << endl;
        cout << "================================" << endl;

        for (int i = 0; i < adjList.size(); i++) {
            cout << "Intersection " << i << " ("
                 << locationNames[i] << ") connects to:" << endl;

            for (auto &neighbor : adjList[i]) {
                cout << "  -> Intersection " << neighbor.first
                     << " (" << locationNames[neighbor.first]
                     << ") - Distance: " << neighbor.second
                     << " km" << endl;
            }

            cout << endl;
        }
    }

    // Depth First Search for road inspections
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);
        visited[start] = true;

        cout << "Road Inspection Route (DFS):" << endl;
        cout << "Purpose: Inspecting connected roads throughout the city."
             << endl;
        cout << "================================" << endl;

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            cout << "Inspecting Intersection " << current
                 << " (" << locationNames[current] << ")" << endl;

            for (auto &neighbor : adjList[current]) {
                int next = neighbor.first;

                if (!visited[next]) {
                    visited[next] = true;
                    s.push(next);
                }
            }
        }

        cout << endl;
    }

    // Breadth First Search for nearby area inspections
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "Nearby Area Inspection (BFS):" << endl;
        cout << "Purpose: Exploring intersections by distance from the starting point."
             << endl;
        cout << "================================" << endl;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << "Checking Intersection " << current
                 << " (" << locationNames[current] << ")" << endl;

            for (auto &neighbor : adjList[current]) {
                int next = neighbor.first;

                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        cout << endl;
    }

    // Find the shortest road distances using Dijkstra's algorithm
    void shortestPaths(int start) {
        vector<int> distance(SIZE, 999999);
        vector<bool> visited(SIZE, false);

        // Distance from the starting intersection to itself is 0
        distance[start] = 0;

        // Visit every intersection
        for (int i = 0; i < SIZE; i++) {
            int current = -1;
            int smallestDistance = 999999;

            // Find the unvisited intersection with the smallest distance
            for (int j = 0; j < SIZE; j++) {
                if (!visited[j] && distance[j] < smallestDistance) {
                    smallestDistance = distance[j];
                    current = j;
                }
            }

            // Stop if no reachable intersection remains
            if (current == -1) {
                break;
            }

            visited[current] = true;

            // Check all roads connected to the current intersection
            for (auto &neighbor : adjList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                int newDistance = distance[current] + weight;

                // Update the distance if a shorter route is found
                if (!visited[next] && newDistance < distance[next]) {
                    distance[next] = newDistance;
                }
            }
        }

        // Display the shortest distances
        cout << "Shortest road distances from Intersection "
             << start << " (" << locationNames[start] << "):" << endl;

        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : "
                 << distance[i] << " km ("
                 << locationNames[i] << ")" << endl;
        }

        cout << endl;
    }

    // Find the Minimum Spanning Tree using Prim's algorithm
    void minimumSpanningTree() {
        vector<int> parent(SIZE, -1);
        vector<int> key(SIZE, 999999);
        vector<bool> visited(SIZE, false);

        // Start building the tree from intersection 0
        key[0] = 0;

        // Find the minimum spanning tree
        for (int i = 0; i < SIZE; i++) {
            int current = -1;
            int smallestWeight = 999999;

            // Find the unvisited intersection with the smallest weight
            for (int j = 0; j < SIZE; j++) {
                if (!visited[j] && key[j] < smallestWeight) {
                    smallestWeight = key[j];
                    current = j;
                }
            }

            if (current == -1) {
                break;
            }

            visited[current] = true;

            // Check the roads connected to the current intersection
            for (auto &neighbor : adjList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                // Update if a cheaper road is found
                if (!visited[next] && weight < key[next]) {
                    key[next] = weight;
                    parent[next] = current;
                }
            }
        }

        // Display the minimum spanning tree
        cout << "Minimum Spanning Tree - City Road Network:" << endl;
        cout << "================================" << endl;

        int totalDistance = 0;

        for (int i = 0; i < SIZE; i++) {
            if (parent[i] != -1) {
                cout << "Road from " << locationNames[parent[i]]
                     << " to " << locationNames[i]
                     << " with distance: " << key[i] << " km"
                     << endl;

                totalDistance += key[i];
            }
        }

        cout << "Total road distance: " << totalDistance << " km"
             << endl << endl;
    }
};

int main() {
    // Names of the city intersections
    vector<string> locationNames = {
        "City Hall",
        "Central Square",
        "Downtown",
        "Public Library",
        "Police Station",
        "Shopping Center",
        "Hospital",
        "School",
        "Fire Station"
    };

    // Connections and distances between intersections
    vector<Edge> edges = {
        {0, 1, 8},
        {0, 2, 21},
        {1, 2, 6},
        {1, 3, 5},
        {1, 4, 4},
        {3, 4, 9},
        {2, 7, 11},
        {2, 8, 8},
        {5, 6, 10},
        {5, 7, 15},
        {5, 8, 5},
        {6, 7, 3},
        {6, 8, 7}
    };

    // Create the city road network
    Graph cityNetwork(edges, locationNames);

    int choice;

    do {
        cout << "\nCity Road Network Manager" << endl;
        cout << "================================" << endl;
        cout << "[1] Display city road network" << endl;
        cout << "[2] Check nearby intersections (BFS)" << endl;
        cout << "[3] Plan road inspection route (DFS)" << endl;
        cout << "[4] Calculate shortest paths" << endl;
        cout << "[5] Find Minimum Spanning Tree" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                cityNetwork.printGraph();
                break;

            case 2:
                cityNetwork.BFS(0);
                break;

            case 3:
                cityNetwork.DFS(0);
                break;

            case 4:
                cityNetwork.shortestPaths(0);
                break;

            case 5:
                cityNetwork.minimumSpanningTree();
                break;

            case 0:
                cout << "Exiting City Road Network Manager. Goodbye!"
                     << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}