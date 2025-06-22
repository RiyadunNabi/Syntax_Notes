#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, m;
vector<vector<int>> adj;
vector<vector<int>> capacity;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t) return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+1);
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

vector<bool> visited;
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0)
            dfs(v);
    }
}

int main() {
    cin >> n >> m;
    adj.assign(n+1, {});
    capacity.assign(n+1, vector<int>(n+1, 0));

    for (int i = 0; i < m; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    }

    int s = 1, t = n;
    cout << "Max Flow: " << maxflow(s, t) << "\n";

    visited.assign(n+1, false);
    dfs(s);

    cout << "Min Cut Edges:\n";
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (visited[u] && !visited[v] && capacity[u][v] == 0)
                cout << u << " -> " << v << "\n";
        }
    }
}