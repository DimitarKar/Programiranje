#include <bits/stdc++.h>
using namespace std;

int n, s, f;
vector<vector<int>> g;
vector<int> par;

int dfs(int x) {
    if(x == f) return INT_MAX;
    for(int i = 0; i < n; i++) {
        if(g[x][i] > 0 && par[i] == -1) {
            par[i] = x;
            int z = dfs(i);
            if(z > 0) return min(z, g[x][i]);
        }
    }
    return 0;
}

int main() {
    int m;
    cin >> n >> m;
    cin >> s >> f;
    g.resize(n, vector<int>(n));
    par.resize(n, -1);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = c;
    }
    int total = 0;
    while(true) {
        for(int i = 0; i < n; i++) par[i] = -1;
        par[s] = -2;
        int flow = dfs(s);
        if(flow == 0) break;
        int k = f;
        cout << f << " ";
        while(k != s) {
            g[par[k]][k] -= flow;
            g[k][par[k]] += flow;
            k = par[k];
            cout << k << " ";
        }
        cout << endl;
        total += flow;
    }
    cout << total;
}
