#include <bits/stdc++.h>
using namespace std;

void push_flow(int u, int v, vector<int>& h, vector<int>& excess, vector<vector<int>>& cap, vector<vector<int>>& flow, queue<int>& q) {
    int d = min(excess[u], cap[u][v] - flow[u][v]);
    
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    
    if (d > 0 && excess[v] == d) {
        q.push(v);
    }
}

void relabel_node(int u, int n, vector<int>& h, vector<vector<int>>& cap, vector<vector<int>>& flow) {
    int min_h = INT_MAX;
    for (int v = 0; v < n; ++v) {
        if (cap[u][v] - flow[u][v] > 0) {
            min_h = min(min_h, h[v]);
        }
    }
    if (min_h < INT_MAX) {
        h[u] = min_h + 1;
    }
}

void discharge(int u, int n, vector<int>& iter, vector<int>& h, vector<int>& excess, vector<vector<int>>& cap, vector<vector<int>>& flow, queue<int>& q) {
    while (excess[u] > 0) {
        if (iter[u] < n) {
            int v = iter[u];
            if (cap[u][v] - flow[u][v] > 0 && h[u] > h[v]) {
                push_flow(u, v, h, excess, cap, flow, q);
            } else {
                iter[u]++; 
            }
        } else {
            relabel_node(u, n, h, cap, flow);
            iter[u] = 0; 
        }
    }
}

int solve_max_flow(int s, int t, int n, vector<vector<int>>& cap) {
    vector<vector<int>> flow(n, vector<int>(n, 0));
    vector<int> h(n, 0);
    vector<int> excess(n, 0);
    vector<int> iter(n, 0);
    queue<int> q;

    h[s] = n;
    excess[s] = INT_MAX; 

    for (int i = 0; i < n; ++i) {
        if (i != s) push_flow(s, i, h, excess, cap, flow, q);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        if (u != s && u != t) {
            discharge(u, n, iter, h, excess, cap, flow, q);
        }
    }
    
    int total_flow = 0;
    for (int i = 0; i < n; ++i) {
        total_flow += flow[i][t];
    }
    return total_flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> cap(n, vector<int>(n, 0));
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        cap[u][v] = w;
    }

    int s, t;
    cin >> s >> t;

    cout << solve_max_flow(s, t, n, cap) << endl;

    return 0;
}
