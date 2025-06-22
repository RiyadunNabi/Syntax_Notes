#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, d;
vector<vector<int>> adj;
vector<vector<int>> capacity;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t)
                    return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n + 3);
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

int main() {
    cin >> n >> d;
    vector<int> profit(n + 1);
    int s = 0, t = n + 1;
    adj.assign(n + 2, {});
    capacity.assign(n + 2, vector<int>(n + 2, 0));

    int total_positive = 0;

    for (int i = 1; i <= n; ++i) {
        cin >> profit[i];
        if (profit[i] > 0) {
            adj[s].push_back(i);
            adj[i].push_back(s);
            capacity[s][i] = profit[i];
            total_positive += profit[i];
        } else {
            adj[i].push_back(t);
            adj[t].push_back(i);
            capacity[i][t] = -profit[i];
        }
    }

    for (int i = 0; i < d; ++i) {
        int a, b;
        cin >> a >> b;
        // If project a is selected, b must be selected too
        // So: add infinite capacity edge from a → b
        adj[a].push_back(b);
        adj[b].push_back(a); // backward edge for residual graph
        capacity[a][b] = INF;
    }

    int flow = maxflow(s, t);
    cout << "Maximum Profit: " << (total_positive - flow) << "\n";
}