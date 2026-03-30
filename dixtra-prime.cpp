#include <bits/stdc++.h>
using namespace std;

void dijkstraPrimes(int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    cout << 2 << " ";
    pq.push({4, 2});

    for (int i = 3; i <= n; i++) {
        if (i < pq.top().first) {
            cout << i << " ";
            pq.push({i * i, i});
        } else {

            while (i == pq.top().first) {
                pair<int, int> top = pq.top();
                pq.pop();
                pq.push({top.first + top.second, top.second});
            }
        }
    }
    cout << endl;
}

int main() {
    dijkstraPrimes(50);
    return 0;
}
