// 検証済み(https://atcoder.jp/contests/agc038/submissions/14129745)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

// 与えられた数列xに対し、
//  y_k = \sum_{i mod k = 0} x_i
// なる変換を行う
void _convert(vector<ll>& x){
    const int sz = x.size();
    for (int k = 1; k < sz; ++k)
        for (int i = k * 2; i < sz; i += k)
            x[k] = (x[k] + x[i]);
}

// 上記の変換の逆変換を行う
void _inverse(vector<ll>& x){
    const int sz = x.size();
    for (int k = sz - 1; k >= 1; --k)
        for (int i = k * 2; i < sz; i += k)
            x[k] = (x[k] - x[i]);
}

// 与えられた数列a, bに対し、gcd畳み込みを行う
// すなわち
//  c_k = \sum_{gcd(i, j)=k} a_i \times b_j
// を求める
vector<ll> gcd_convolution(vector<ll> a, vector<ll> b){
    _convert(a); _convert(b);
    vector<ll> c(max(a.size(), b.size()));
    for (int i = 0; i < c.size(); ++i)
        c[i] = (i < (int)a.size() ? a[i] : 0LL) * (i < (int)b.size() ? b[i] : 0LL);
    _inverse(c);
    return c;
}
