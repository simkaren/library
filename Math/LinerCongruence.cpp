// 検証済み(https://yukicoder.me/submissions/380304)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

/* aとbの最大公約数を求める. */
ll gcd(ll a, ll b){
    if (b > a) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}

/* ax+by=gcd(a,b)を満たす(x,y)を格納し、gcd(a,b)を返す. */
ll extgcd(ll a, ll b, ll& x, ll& y){
    if (b > a) return extgcd(b, a, y, x);
    if (b == 0){
        x = 1; y = 0;
        return a;
    }
    ll g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

/* mod mでのaの逆元を求める.(gcd(a,m) = 1) */
ll modinv(ll a, ll m){
    ll x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}

/* 連立線形方程式を解く.
        A[i] * x ≡ B[i] (mod M[i])
    なる方程式の解が
        x ≡ b (mod m)
    とかけるとき、(b, m)を返す.(存在しなければ(0, -1)) */
pair<ll, ll> liner_congruence(
    vector<ll> A, vector<ll> B, vector<ll> M
){
    ll x = 0, m = 1;

    for (int i = 0; i < A.size(); ++i){
        ll a = A[i] * m,
         b = B[i] - A[i] * x,
         d = gcd(M[i], a);

        if (b % d != 0) // 解なし
            return make_pair(0, -1);
        
        ll t = b / d * modinv(a / d, M[i] / d) % (M[i] / d);
        x = x + m * t;
        m *= M[i] / d;
    }

    return make_pair(x % m, m);
}

signed main(){
    vector<ll> a(3);
    a[0] = a[1] = a[2] = 1;
    vector<ll> b(3), m(3);
    for (int i = 0; i < 3; ++i){
        ll x, y; cin >> x >> y;
        b[i] = x; m[i] = y;
    }
    
    auto ans = liner_congruence(a, b, m);
    if (ans.second == -1)
        cout << -1 << endl;
    else if (ans.first > 0)
        cout << ans.first << endl;
    else
        cout << (ans.first + ans.second) << endl;
    
    return 0;
}