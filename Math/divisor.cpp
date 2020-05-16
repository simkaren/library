#include <bits/stdc++.h>

using namespace std;

#define ll long long

/* kの約数を求める. 時間計算量O(√k) */
vector<ll> divisor(ll k){
    vector<ll> d;
    for (ll i = 1;i * i <= k;++i){
        if (k % i == 0){
            d.push_back(i);
            if (i * i != k)
                d.push_back(k / i);
        }
    }
    sort(d.begin(),d.end());
    return d;
}