#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int maxn = 100;
    int maxinf = 1000000000;
    int matrica[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) matrica[i][j] = 0;
            else matrica[i][j] = maxinf;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        matrica[a][b] = t;
        matrica[b][a] = t;
    }
    int start;
    cin >> start;
    int dalecina[100];
    bool posecen[100];
    for (int i = 0; i < n; i++) {
        dalecina[i] = maxinf;
        posecen[i] = false;
    }
    dalecina[start] = 0;
    for (int k = 0; k < n; k++) {
        int minv = -1;
        for (int i = 0; i < n; i++) {
            if (!posecen[i] && (minv == -1 || dalecina[i] < dalecina[minv])) {
                minv = i;
            }
        }
        if (dalecina[minv] == maxinf) break;
        posecen[minv] = true;
        for (int i = 0; i < n; i++) {
            if (dalecina[minv] + matrica[minv][i] < dalecina[i]) {
                dalecina[i] = dalecina[minv] + matrica[minv][i];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dalecina[i] == maxinf) cout << "INF\n";
        else cout << dalecina[i] << "\n";
    }
}
