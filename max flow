Sure! Here are 3 Max Flow coding problems (from easy to medium-hard) with C++ solutions using Edmonds-Karp (BFS-based Ford-Fulkerson) algorithm. Great for DSA problem-solving tests.


---

🧠 Problem 1: Maximum Bipartite Matching

Description: You're given n jobs and m workers. A worker can do some jobs. Find the maximum number of jobs that can be assigned such that each worker does at most 1 job and each job is assigned to one worker.

Input:

n, m (number of jobs and workers)

A binary matrix graph[i][j] where 1 means worker i can do job j


Solution Idea: Convert to a max flow problem:

Source to workers (capacity = 1)

Workers to jobs (if graph[i][j] == 1, capacity = 1)

Jobs to sink (capacity = 1)


✅ C++ Code:

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, m; // n workers, m jobs
vector<vector<int>> adj;
vector<vector<int>> capacity;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(t+1);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
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
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> graph[i][j];

    int V = n + m + 2;
    int s = n + m;
    int t = n + m + 1;
    adj.assign(V, {});
    capacity.assign(V, vector<int>(V, 0));

    for (int i = 0; i < n; ++i) {
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i] = 1;
    }

    for (int i = 0; i < m; ++i) {
        adj[n+i].push_back(t);
        adj[t].push_back(n+i);
        capacity[n+i][t] = 1;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (graph[i][j]) {
                adj[i].push_back(n+j);
                adj[n+j].push_back(i);
                capacity[i][n+j] = 1;
            }

    cout << maxflow(s, t) << endl;
}


---

💧 Problem 2: Internet Bandwidth

Description: Given a network of routers and bandwidth between them, find the maximum possible bandwidth from source to sink.

Input:

n nodes, m edges

Each edge has (u, v, capacity)


✅ C++ Code: Similar to Problem 1. Use same maxflow() and bfs() function. Input edges and build adj and capacity matrices accordingly.


---

🏭 Problem 3: Project Selection

Description: You have a list of n projects. Each project has a profit (can be negative = cost). Some projects depend on others. Choose a set of projects to maximize total profit, under dependency constraints.

Model:

Create source-sink graph

For project with profit p > 0, connect source → project with capacity p

For p < 0, connect project → sink with capacity -p

Add dependency edges (if A depends on B, add infinite capacity from A → B)


Total profit = sum(all positive profits) - maxflow()


---

Would you like me to send Problem 2 and 3 full code too, or do you want to solve them on your own using the pattern?

Also, do you want to try Dinic's algorithm version later?

