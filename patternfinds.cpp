#include <bits/stdc++.h>
using namespace std;

vector<int> rabin_karp(string& t, string& s)
{
    int p = 31;
    int mod = 1e9 + 7;

    int slen = s.length();
    int tlen = t.length();

    if (slen > tlen) {
        return {};
    }

    vector<long long> deg(tlen + 1);
    deg[0] = 1;
    for (int i = 1; i <= tlen; i++) {
        deg[i] = (deg[i - 1] * p) % mod;
    }

    vector<long long> hash_t(tlen + 1, 0);
    for (int i = 0; i < tlen; i++) {
        long long char_val = t[i] - 'a' + 1;
        hash_t[i + 1] = (hash_t[i] + char_val * deg[i]) % mod;
    }

    long long hash_s = 0;
    for (int i = 0; i < slen; i++) {
        long long char_val = s[i] - 'a' + 1;
        hash_s = (hash_s + char_val * deg[i]) % mod;
    }

    vector<int> occurances;
    for (int i = 0; i <= tlen - slen; i++) {
        long long cur_h = (hash_t[i + slen] + mod - hash_t[i]) % mod;

        if (cur_h == (hash_s * deg[i]) % mod) {
            occurances.push_back(i);
        }
    }
    return occurances;
}

int main()
{
    int T;
    cin >> T;

    vector<pair<int, vector<int>>> rezultati;

    for (int i = 0; i < T; i++) {
        string a, b;
        cin >> a >> b;
        vector<int> temp = rabin_karp(a, b);
        rezultati.push_back({temp.size(), temp});
    }

    for (int i = 0; i < T; i++) {
        int count = rezultati[i].first;
        vector<int>& positions = rezultati[i].second;

        if (count == 0) {
            cout << "Not Found\n\n";
        } else {
            cout << count << '\n';
            for (int pos : positions) {
                cout << pos + 1 << " ";
            }
            cout << "\n\n";
        }
    }

    return 0;
}
