#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct RollingHash{
    string text; // text
    int n; // number of characters
    int base1 = 1009, base2 = 1007;
    ll mod1 = (ll)1e9 + 9, mod2 = (ll)1e9 + 7;
    ll* pow1;
    ll* pow2;
    ll* hash1;
    ll* hash2;
    /* constructor */
    RollingHash(string s){
        text = s;
        n = text.size();
        hash1 = new ll[n + 1];
        hash2 = new ll[n + 1];
        pow1 = new ll[n + 1];
        pow2 = new ll[n + 1];
        hash1[0] = hash2[0] = 0;
        pow1[0] = pow2[0] = 1;
        for (int i = 0;i < n;++i){
            hash1[i + 1] = (hash1[i] + text[i]) * base1 % mod1;
            hash2[i + 1] = (hash2[i] + text[i]) * base2 % mod2;
            pow1[i + 1] = pow1[i] * base1 % mod1;
            pow2[i + 1] = pow2[i] * base2 % mod2;
        }
    }
    /* メモリの開放 */
    void free(){ delete[] pow1,pow2,hash1,hash2; }
    /* text[l,l+1,...,r-1]のハッシュ値を計算 */
    pair<ll,ll> get(int l,int r){
        pair<ll,ll> p;
        p.first = ((hash1[r] - hash1[l] * pow1[r - l] % mod1) + mod1) % mod1;
        p.second = ((hash2[r] - hash2[l] * pow2[r - l] % mod2) + mod2) % mod2;
        return p;
    }
};
