#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rabin_karp_dup(int len, string &s) {
        if (len == 0) return -1;
        long long p = 31;
        long long m = 1e9+9;
        int n = s.size();

        vector<long long> p_pow(n);
        p_pow[0] = 1;
        for (int i=1; i<n; i++)
            p_pow[i] = (p_pow[i-1] * p) % m;

        vector<long long> h(n+1, 0);
        for (int i=0; i<n; i++)
            h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;

        unordered_map<long long, vector<int>> mp;
        mp.reserve(n*2);

        for (int i=0; i+len<=n; i++) 
        {
            long long cur_h = (h[i+len] + m - h[i]) % m;
            cur_h = (cur_h * p_pow[n - i - len]) % m;

            auto it = mp.find(cur_h);
            if (it != mp.end()) 
            {
                for (int j : it->second) 
                {
                    if (s.compare(i, len, s, j, len) == 0)
                        return i;
                }
            }
            mp[cur_h].push_back(i);
        }
        return -1;
    }

    string longestDupSubstring(string s) {
        int n = s.size();
        int L = 1, R = n - 1, best = 0, bestPos = -1;

        while (L <= R) 
        {
            int mid = (L + R) / 2;
            int pos = rabin_karp_dup(mid, s);
            if (pos != -1) 
            {
                best = mid;
                bestPos = pos;
                L = mid + 1;
            } 
            else 
            {
                R = mid - 1;
            }
        }

        if (bestPos == -1) return "";
        return s.substr(bestPos, best);
    }
};
