
#include <bits/stdc++.h>
using namespace std;

const int BESK = 1e9;

int main() {
    int jazli, rebra;
    cin >> jazli >> rebra;
    vector<vector<int>> dalecina(jazli, vector<int>(jazli, BESK));

    for (int i = 0; i < jazli; i++) dalecina[i][i] = 0;

    for (int i = 0; i < rebra; i++) {
        int a, b, tezina;
        cin >> a >> b >> tezina;
        dalecina[a][b] = min(dalecina[a][b], tezina);
    }

    for (int k = 0; k < jazli; k++)
        for (int i = 0; i < jazli; i++)
            for (int j = 0; j < jazli; j++)
                if (dalecina[i][k] < BESK && dalecina[k][j] < BESK)
                    dalecina[i][j] = min(dalecina[i][j], dalecina[i][k] + dalecina[k][j]);

    for (int i = 0; i < jazli; i++) {
        for (int j = 0; j < jazli; j++) {
            if (dalecina[i][j] == BESK) cout << "INF ";
            else cout << dalecina[i][j] << " ";
        }
        cout << "\n";
    }
}
