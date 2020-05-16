#include <bits/stdc++.h>

using namespace std;

#define ll long long

// 素因数分解する
vector<ll> prime_factor(ll n){
    map<ll, int> ret;
    for (ll i = 2; i * i <= n; ++i){
        while (n % i == 0){
            ++ret[i]; n /= i;
        }
    }
    if (n != 1) ret[n] = 1;
    vector<ll> pf;
    for (auto p : ret)
        while (p.second--)
            pf.push_back(p.first);
    return pf;
}