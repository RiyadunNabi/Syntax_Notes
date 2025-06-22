#include <bits/stdc++.h>
using namespace std;

#define V 6
const int INF = INT_MAX;

// BFS to find augmenting path from source to sink
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    fill(visited, visited + V, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && rGraph[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return visited[t];
}

int fordFulkerson(int graph[V][V], int s, int t, int rGraph[V][V]) {
    int u, v;

    // Initialize residual graph
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INF;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}

void findMinCutEdges(int graph[V][V], int rGraph[V][V], int s) {
    // Step 1: BFS on residual graph to find reachable vertices
    bool visited[V];
    fill(visited, visited + V, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; ++v) {
            if (rGraph[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // Step 2: Print edges from reachable → unreachable with capacity > 0 in original graph
    cout << "Min-Cut Edges:\n";
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (visited[u] && !visited[v] && graph[u][v] > 0) {
                cout << u << " -> " << v << "\n";
            }
        }
    }
}

int main() {
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    int rGraph[V][V]; // Residual graph

    int maxFlow = fordFulkerson(graph, 0, 5, rGraph);
    cout << "Maximum Flow: " << maxFlow << "\n";

    findMinCutEdges(graph, rGraph, 0);

    return 0;
}