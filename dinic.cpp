#include <bits/stdc++.h>
using namespace std;

struct E {
    int to, rev;
    long long cap;
};

class Flow {
public:
    int n;
    vector<vector<E>> g;
    vector<int> lvl, nxt;
    const long long INF = 1e18;

    Flow(int n) {
        this->n = n;
        g.resize(n);
        lvl.resize(n);
        nxt.resize(n);
    }

    void addEdge(int a, int b, long long c) {
        g[a].push_back({b, (int)g[b].size(), c});
        g[b].push_back({a, (int)g[a].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q;
        q.push(s);
        lvl[s] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) {
                if (e.cap > 0 && lvl[e.to] == -1) {
                    lvl[e.to] = lvl[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return lvl[t] != -1;
    }

    long long dfs(int v, int t, long long f) {
        if (v == t || f == 0) return f;
        for (int &i = nxt[v]; i < (int)g[v].size(); i++) {
            E &e = g[v][i];
            if (lvl[e.to] == lvl[v] + 1 && e.cap > 0) {
                long long pushed = dfs(e.to, t, min(f, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long getFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(nxt.begin(), nxt.end(), 0);
            while (true) {
                long long pushed = dfs(s, t, INF);
                if (!pushed) break;
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    Flow f(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        f.addEdge(a, b, c);
    }
    int s, t;
    cin >> s >> t;
    cout << f.getFlow(s, t) << endl;

}
