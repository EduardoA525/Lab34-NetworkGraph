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

    // Display the network
    cityNetwork.printGraph();

    // Perform road inspections starting from City Hall
    cityNetwork.DFS(0);
    cityNetwork.BFS(0);

    return 0;
}
