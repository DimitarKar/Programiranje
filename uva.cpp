#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int najdiPat(int jazol, const int kraj, int kolkJazli,
             vector<vector<int>>& kap, vector<int>& pred) {
    if (jazol == kraj) return INT_MAX;

    for (int sled = 0; sled < kolkJazli; ++sled) {
        if (kap[jazol][sled] > 0 && pred[sled] == -1) {
            pred[sled] = jazol;
            int protok = najdiPat(sled, kraj, kolkJazli, kap, pred);
            if (protok > 0) return min(protok, kap[jazol][sled]);
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int kolkJazli, kolkRebra;
    cin >> kolkJazli >> kolkRebra;

    int pocJazol, krJazol;
    cin >> pocJazol >> krJazol;

    struct Rebro { int od, do_, kap; };
    vector<Rebro> rebra(kolkRebra);

    for (int i = 0; i < kolkRebra; ++i)
        cin >> rebra[i].od >> rebra[i].do_ >> rebra[i].kap;

    int najProtok = INT_MAX, kritIdx = -1;

    for (int i = 0; i < kolkRebra; ++i) {
        vector<vector<int>> rez(kolkJazli, vector<int>(kolkJazli, 0));
        for (int j = 0; j < kolkRebra; ++j) {
            if (i == j) continue;
            rez[rebra[j].od][rebra[j].do_] = rebra[j].kap;
        }

        int segProtok = 0;
        while (true) {
            vector<int> pred(kolkJazli, -1);
            pred[pocJazol] = -2;
            int patProtok = najdiPat(pocJazol, krJazol, kolkJazli, rez, pred);
            if (patProtok == 0) break;

            segProtok += patProtok;
            int v = krJazol;
            while (v != pocJazol) {
                int u = pred[v];
                rez[u][v] -= patProtok;
                rez[v][u] += patProtok;
                v = u;
            }
        }

        if (segProtok < najProtok) {
            najProtok = segProtok;
            kritIdx = i;
        }
    }

    cout << najProtok << " " << kritIdx << "\n";
    return 0;
}
