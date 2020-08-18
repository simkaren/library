// 検証済み(https://judge.yosupo.jp/submission/16746)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

template<ll mod = 998244353LL, ll root = 3LL>
void ntt(vector<ll>& a, bool rev = false){
    auto modpow = [](ll p, int q){
        ll res = 1LL;
        while (q){
            if (q & 1) res = res * p % mod;
            p = p * p % mod;
            q >>= 1;
        }
        return res;
    };
    const int sz = a.size();
    if (sz == 1) return;
    vector<ll> b(sz);
    int r = rev ? (mod - 1 - (mod - 1) / sz) : (mod - 1) / sz;
    ll s = modpow(root, r);
    vector<ll> kp(sz / 2 + 1, 1);
    for(int i = 0; i < sz / 2; ++i) kp[i + 1] = kp[i] * s % mod;
    for(int i = 1, l = sz / 2; i < sz; i <<= 1, l >>= 1){
        for(int j = 0, r = 0; j < l; ++j, r += i){
            for(int k = 0, s = kp[i * j]; k < i; ++k){
                ll p = a[k + r], q = a[k + r + sz / 2];
                b[k + 2 * r] = (p + q) % mod;
                b[k + 2 * r + i] = ((p - q) % mod + mod) % mod * s % mod;
            }
        }
        swap(a, b);
    }
    if(rev){
        s = modpow(sz, mod - 2);
        for(int i = 0; i < sz; i++){ a[i] = a[i] * s % mod; }
    }
}

template<ll mod = 998244353LL, ll root = 3LL>
vector<ll> convolute(vector<ll> a, vector<ll> b){
    const int sz = (int)a.size() + (int)b.size() - 1;
    int t = 1;
    while (t < sz) t *= 2;
    a.resize(t, 0); b.resize(t, 0);
    ntt<mod, root>(a); ntt<mod, root>(b);
    for (int i = 0; i < t; ++i)
        a[i] = a[i] * b[i] % mod;
    ntt<mod, root>(a, true);
    a.resize(sz);
    return a;
}

constexpr ll mod = 998244353LL;

int main(void){
    int N, M; cin >> N >> M;
    vector<ll> a(N), b(M);
    for (auto& ai : a) cin >> ai;
    for (auto& bi : b) cin >> bi;
    vector<ll> c = convolute<>(a, b);
    for (auto ci : c)
        cout << ci << " ";
    cout << endl;
	return 0;
}