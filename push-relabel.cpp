#include <bits/stdc++.h>
using namespace std;


struct Edge {
    int to;
    int rev;
    long long cap;  
    Edge(int _to, int _rev, long long _cap) : to(_to), rev(_rev), cap(_cap) {}
};

struct PushRelabel {
    int n;
    vector<vector<Edge>> g;
    vector<long long> excess;
    vector<int> height;
    vector<int> cur;      
    vector<int> countH;   
    deque<int> activeQ;   
    int s, t;

    PushRelabel(int n_) : n(n_), g(n_), excess(n_, 0), height(n_, 0), cur(n_, 0), countH(2*n_+5, 0) {}

    void addEdge(int u, int v, long long c) {
        
        g[u].emplace_back(v, (int)g[v].size(), c);
    
        g[v].emplace_back(u, (int)g[u].size()-1, 0);
    }

    void push(Edge &e, int u) {
        if (e.cap == 0) return;
        int v = e.to;
        long long amt = min(excess[u], e.cap);
        if (amt <= 0 || height[u] != height[v] + 1) return;
        e.cap -= amt;
        g[v][e.rev].cap += amt;
        excess[u] -= amt;
        excess[v] += amt;
        if (amt > 0 && v != s && v != t && excess[v] == amt) {
            activeQ.push_back(v);
        }
    }

    void relabel(int u) {
        int minH = INT_MAX;
        for (auto &e : g[u]) {
            if (e.cap > 0) {
                minH = min(minH, height[e.to]);
            }
        }
        if (minH < INT_MAX) {
        
            countH[height[u]]--;
            height[u] = minH + 1;
            countH[height[u]]++;
            cur[u] = 0; 
        } else {
            
            countH[height[u]]--;
            height[u] = n + 1;
            countH[height[u]]++;
            cur[u] = 0;
        }
    }

    void gapHeuristic(int k) {
 
        for (int v = 0; v < n; ++v) {
            if (v == s || v == t) continue;
            if (height[v] > k && height[v] <= n) {
                countH[height[v]]--;
                height[v] = n + 1;
                countH[height[v]]++;
                cur[v] = 0;
            }
        }
    }

    long long maxflow(int s_, int t_) {
        s = s_;
        t = t_;
        height.assign(n, 0);
        excess.assign(n, 0);
        cur.assign(n, 0);
        countH.assign(2*n+5, 0);
        activeQ.clear();

        height[s] = n;
        countH[0] = n - 1; 
        countH[n] = 1;

        
        for (auto &e : g[s]) {
            if (e.cap > 0) {
                long long amt = e.cap;
                e.cap -= amt;
                g[e.to][e.rev].cap += amt;
                excess[e.to] += amt;
                excess[s] -= amt;
                if (e.to != s && e.to != t) activeQ.push_back(e.to);
            }
        }

        while (!activeQ.empty()) {
            int u = activeQ.front();
            activeQ.pop_front();
            if (u == s || u == t) continue;
            if (excess[u] <= 0) continue;

            bool pushed = false;
            while (excess[u] > 0) {
                if (cur[u] < (int)g[u].size()) {
                    Edge &e = g[u][cur[u]];
                    if (e.cap > 0 && height[u] == height[e.to] + 1) {
                        push(e, u);
                        pushed = true;
                    } else {
                        cur[u]++;
                    }
                } else {
                    int oldH = height[u];
                    relabel(u);
                    if (countH[oldH] == 0) {
                        gapHeuristic(oldH);
                    }
                }
            }

            if (excess[u] > 0) {
                activeQ.push_back(u);
            }
        }
        long long flow = 0;
        for (auto &e : g[t]) {
        }
        return excess[t];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) {
        cerr << "Neispraven vlez\n";
        return 0;
    }
    PushRelabel pr(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        u--; v--;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cerr << "Edge vertex nadvor od range\n";
            return 0;
        }
        pr.addEdge(u, v, c);
    }
    int s, t;
    cin >> s >> t;
    s--; t--;
    long long result = pr.maxflow(s, t);
    cout << result << '\n';
    return 0;
}

