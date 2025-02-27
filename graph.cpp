#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;

class Graph {
private:
    unordered_map<int, list<int>> adjacentList;
    bool isDirected;

    vector<vector<int>> getEdges() const {
        vector<vector<int>> edges;
        for (const auto& pair : adjacentList) {
            int u = pair.first;
            for (int v : pair.second) {
                if (!isDirected && u > v) {
                    continue;
                }
                edges.push_back({u, v});
            }
        }
        return edges;
    }

public:
    Graph() {
        isDirected = false;
    }

    void setUndirected() {
        isDirected = false;
    }

    void addEdge(int node1, int node2) {
        adjacentList[node1].push_back(node2);
        if (!isDirected) {
            adjacentList[node2].push_back(node1);
        }
    }

    void bfs(int start) {
        vector<bool> visited(adjacentList.size(), false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            cout << current << " ";
            q.pop();

            for (int neighbor : adjacentList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void dfs(int startVertex) {
        vector<bool> visited(adjacentList.size(), false);
        stack<int> stack;

        stack.push(startVertex);

        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();

            if (!visited[current]) {
                cout << current << " ";
                visited[current] = true;
                
                for (auto it = adjacentList[current].rbegin(); it != adjacentList[current].rend(); ++it) {
                    if (!visited[*it]) {
                        stack.push(*it);
                    }
                }
            }
        }
    }

    vector<vector<int>> findCycles() {
        vector<vector<int>> edges = getEdges();
        vector<vector<int>> cycles;

        auto rotateToSmallest = [](vector<int> path) {
            if (path.empty()) return path;
            auto minIt = min_element(path.begin(), path.end());
            rotate(path.begin(), minIt, path.end());
            return path;
        };

        auto invert = [rotateToSmallest](vector<int> path) {
            reverse(path.begin(), path.end());
            return rotateToSmallest(path);
        };

        auto isNew = [&cycles](const vector<int>& path) {
            return find(cycles.begin(), cycles.end(), path) == cycles.end();
        };

        function<void(vector<int>, vector<vector<int>>&)> findNewCycles;

        findNewCycles = [&](vector<int> path, vector<vector<int>>& graph) {
            int startNode = path[0];
            for (auto& edge : graph) {
                int node1 = edge[0], node2 = edge[1];
                if (startNode == node1 || startNode == node2) {
                    int nextNode = (node1 == startNode) ? node2 : node1;
                    auto it = find(path.begin(), path.end(), nextNode);
                    if (it == path.end()) {
                        vector<int> newPath = {nextNode};
                        newPath.insert(newPath.end(), path.begin(), path.end());
                        findNewCycles(newPath, graph);
                    } else if (path.size() > 2 && nextNode == path.back()) {
                        vector<int> p = rotateToSmallest(path);
                        vector<int> inv = invert(p);
                        if (isNew(p) && isNew(inv)) {
                            cycles.push_back(p);
                        }
                    }
                }
            }
        };

        for (auto& edge : edges) {
            for (int node : edge) {
                findNewCycles({node}, edges);
            }
        }

        return cycles;
    }
};

int main() {
    Graph graph;
    graph.setUndirected();

    graph.addEdge(0, 1); // A - B
    graph.addEdge(0, 3); // A - D
    graph.addEdge(0, 5); // A - F
    graph.addEdge(1, 2); // B - C
    graph.addEdge(1, 3); // B - D
    graph.addEdge(1, 4); // B - E
    graph.addEdge(2, 4); // C - E
    graph.addEdge(2, 5); // C - F
    graph.addEdge(2, 3); // C - D
    graph.addEdge(3, 5); // D - F

    cout << "BFS starting from node 0: ";
    graph.bfs(0);
    cout << endl;

    cout << "DFS starting from node 0: ";
    graph.dfs(0);
    cout << endl;

    vector<vector<int>> cycles = graph.findCycles();
    cout << "Number of cycles in the graph: " << cycles.size() << endl;
    cout << "Cycles in the graph:" << endl;
    for (const auto& cycle : cycles) {
        for (size_t i = 0; i < cycle.size(); i++) {
            cout << cycle[i];
            if (i != cycle.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}