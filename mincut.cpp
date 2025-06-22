#include <bits/stdc++.h>
using namespace std;

#define V 6
const int INF = INT_MAX;

bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    fill(visited, visited + V, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return visited[t];
}

// Find all reachable vertices from s in residual graph
void dfs(int rGraph[V][V], int s, bool visited[]) {
    visited[s] = true;
    for (int i = 0; i < V; i++) {
        if (rGraph[s][i] > 0 && !visited[i])
            dfs(rGraph, i, visited);
    }
}

int fordFulkerson(int graph[V][V], int s, int t, vector<pair<int, int>>& minCutEdges) {
    int u, v;

    int rGraph[V][V];
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

    // BFS or DFS from source to mark reachable vertices in rGraph
    bool visited[V];
    fill(visited, visited + V, false);
    dfs(rGraph, s, visited);

    // Find all edges from reachable to non-reachable in original graph (min cut)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (visited[i] && !visited[j] && graph[i][j] > 0) {
                minCutEdges.push_back({i, j});
            }
        }
    }

    return max_flow;
}

int main() {
    int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };

    vector<pair<int, int>> minCutEdges;
    int maxFlow = fordFulkerson(graph, 0, 5, minCutEdges);

    cout << "The maximum possible flow is " << maxFlow << endl;

    cout << "Min-Cut Edges are:\n";
    for (auto [u, v] : minCutEdges) {
        cout << u << " -> " << v << "\n";
    }

    return 0;
}