//Eduardo Avila
//COMSC - 210 - 5293
//Lab 34 - Network Graph 1

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    // Build the graph using the given edges
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // Add the edge in both directions
            adjList[src].push_back({dest, weight});
            adjList[dest].push_back({src, weight});
        }
    }

    // Display the adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;

        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";

            for (auto &neighbor : adjList[i]) {
                cout << "(" << neighbor.first << ", "
                     << neighbor.second << ") ";
            }

            cout << endl;
        }
    }

    // Depth First Search using a stack
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);
        visited[start] = true;

        cout << "DFS starting from vertex " << start << ":" << endl;

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            cout << current << " ";

            // Visit unvisited neighbors
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

    // Breadth First Search using a queue
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << current << " ";

            // Visit unvisited neighbors
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
    // Original graph
    vector<Edge> edges = {
        {0, 1, 12},
        {0, 2, 8},
        {0, 3, 21},
        {2, 3, 6},
        {2, 6, 2},
        {5, 6, 6},
        {4, 5, 9},
        {2, 4, 4},
        {2, 5, 5}
    };

    Graph graph(edges);

    graph.printGraph();

    cout << endl;

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}