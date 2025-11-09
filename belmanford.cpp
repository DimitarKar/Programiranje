#include <bits/stdc++.h>
using namespace std;

struct Edge { int u,v,w; };

int main() {
    int n,m;
    cin>>n>>m;
    vector<Edge> e;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        e.push_back({a,b,c});
    }
    vector<int> d(n,1e9);
    d[0]=0;
    for(int i=0;i<n-1;i++)
        for(auto x:e)
            if(d[x.u]+x.w<d[x.v]) d[x.v]=d[x.u]+x.w;
    for(auto x:e)
        if(d[x.u]+x.w<d[x.v]) { cout<<"Negative cycle\n"; return 0; }
    for(int i=0;i<n;i++) cout<<d[i]<<" ";
}
