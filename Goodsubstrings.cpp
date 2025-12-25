#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef long long ll;

ll presmetaj_hash(int pocetok, int kraj, const vector<ll>& h_niza, const vector<ll>& p_stepeni, int dolzina_s, ll modul)
{
    ll rezultat = (h_niza[kraj + 1] - h_niza[pocetok] + modul) % modul;
    rezultat = (rezultat * p_stepeni[dolzina_s - pocetok]) % modul;
    return rezultat;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string tekst_s, loshi_bukvi;
    int maks_losi;
    cin >> tekst_s >> loshi_bukvi >> maks_losi;

    int n = tekst_s.size();
    vector<int> prefiks_losi(n + 1, 0);

    for (int i = 0; i < n; ++i)
    {
        int dali_e_losh = (loshi_bukvi[tekst_s[i] - 'a'] == '0');
        prefiks_losi[i + 1] = prefiks_losi[i] + dali_e_losh;
    }


    const ll modul = 1e9 + 9;
    const ll baza_p = 31;

    vector<ll> p_stepeni(n + 1);
    p_stepeni[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        p_stepeni[i] = (p_stepeni[i - 1] * baza_p) % modul;
    }

    vector<ll> h_niza(n + 1, 0);
    for (int i = 0; i < n; ++i)
    {
        h_niza[i + 1] = (h_niza[i] + (tekst_s[i] - 'a' + 1) * p_stepeni[i]) % modul;
    }

    unordered_set<ll> unikatni_hashovi;
    unikatni_hashovi.reserve(1e5);

    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            int tekovni_losi = prefiks_losi[j + 1] - prefiks_losi[i];

            if (tekovni_losi > maks_losi)
            {
                break;
            }

            ll tekovna_hash = presmetaj_hash(i, j, h_niza, p_stepeni, n, modul);
            unikatni_hashovi.insert(tekovna_hash);
        }
    }

    cout << unikatni_hashovi.size() << '\n';

    return 0;
}
