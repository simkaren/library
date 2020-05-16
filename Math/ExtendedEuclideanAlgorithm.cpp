// 検証済み(https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

/* ax+by=gcd(a,b)を満たす(x,y)を格納し、gcd(a,b)を返す. */
ll extgcd(ll a, ll b, ll& x, ll& y){
    if (b > a) return extgcd(b, a, y, x);
    if (b == 0){
        x = 1; y = 0;
        return a;
    }
    int g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

signed main(){
    ll a, b; cin >> a >> b;
    ll x, y;
    extgcd(a, b, x, y);
    cout << x << " " << y << endl;
    return 0;
}