#include <bits/stdc++.h>
using namespace std;

struct Hasher 
{
    long long p=31;
    long long m=1e9+9;
    int n;
    vector<long long> p_pow, h, rh;

    Hasher(const string &s) 
    {
        n = s.size();
        p_pow.resize(n+1);
        h.resize(n+1);
        rh.resize(n+1);

        p_pow[0] = 1;
        for (int i=1; i<=n; i++)
            p_pow[i] = (p_pow[i-1] * p) % m;

        for (int i=0; i<n; i++)
            h[i+1] = (h[i] + (s[i]-'a'+1) * p_pow[i]) % m;

        string t = s;
        reverse(t.begin(), t.end());

        for (int i=0; i<n; i++)
            rh[i+1] = (rh[i] + (t[i]-'a'+1) * p_pow[i]) % m;
    }

    long long hashuvaj(int l, int r)
    {
        long long res = (h[r+1] - h[l] + m) % m;
        return (res * p_pow[n-r-1]) % m;
    }

    long long obratnohashuvaj(int l, int r)
    {
        long long res = (rh[r+1] - rh[l] + m) % m;
        return (res * p_pow[n - r - 1]) % m;
    }

    bool is_pal(int l, int r)
    {
        int rl = n-1-r;
        int rr = n-1-l;
        return hashuvaj(l, r) == obratnohashuvaj(rl, rr);
    }
};

int main() 
{
    string s;
    cin >> s;
    int n = s.size();

    Hasher H(s);

    vector<vector<int>> pc(n, vector<int>(n+1, 0));
    vector<long long> ans(n+2, 0);

    for (int len=1; len<=n; len++)
    {
        for (int i=0; i+len-1<n; i++)
        {
            int j=i+len-1;
            if (!H.is_pal(i, j)) continue;
            pc[i][len] = 1;
            int half = len/2;
            if (half>0 && H.is_pal(i, i+half-1))
            {
                pc[i][len]=pc[i][half]+1;
            }
            else
            {
                pc[i][len]=1;
            }
            ans[pc[i][len]]++;
        }
    }
    for (int k=n; k>=1; k--)
    {
        ans[k]+=ans[k+1];
    }
    for (int k=1; k<=n; k++) 
    {
        cout << ans[k] << " ";
    }
    cout << "\n";

    return 0;
}
