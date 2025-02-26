#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:
    unordered_map<int, list<int>> adjacentList;
    bool isDirected;

    bool dfsCycleDetection(int node, int parent, vector<bool>& visited, int& cycleCount) {
        visited[node] = true;

        for (int neighbor : adjacentList[node]) {
            if (!visited[neighbor]) {
                if (dfsCycleDetection(neighbor, node, visited, cycleCount)) {
                    return true;
                }
            } 
            else if (neighbor != parent) {
                cycleCount++;
            }
        }
        return false;
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

    int countCycles() {
        int cycleCount = 0;
        vector<bool> visited(adjacentList.size(), false);

        for (auto& pair : adjacentList) {
            int node = pair.first;
            if (!visited[node]) {
                dfsCycleDetection(node, -1, visited, cycleCount);
            }
        }

        return cycleCount / 2;
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

    cout << "Number of cycles in the graph: " << graph.countCycles() << endl;

    return 0;
}