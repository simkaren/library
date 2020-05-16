// 検証済み(https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_C)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

/* aとbの最大公約数を求める. */
ll gcd(ll a, ll b){
    if (b > a) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}

/* aとbの最小公倍数を求める. */
ll lcm(ll a, ll b){
    ll g = gcd(a, b);
    return (a / g) * b;
}

signed main(){
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    
    ll lcm = 1;
    for (auto ai : a){
        ll g = gcd(lcm, ai);
        lcm = g * (lcm / g) * (ai / g);
    }

    cout << lcm << endl;

    return 0;
}