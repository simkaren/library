#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll mod = 1000000007LL;

ll modpow(ll a, ll b){
    if (b == 0) return 1;
    ll tmp = modpow(a, b / 2);
    if (b & 1) 
        return tmp * tmp % mod * a % mod;
    return tmp * tmp % mod;
}

ll inverse(ll k){
    return modpow(k, mod - 2);
}

struct Matrix {
    int n;
    vector<vector<ll>> element;

    Matrix(int n) : n(n) {
        element.resize(n);
        for (int i = 0; i < n; ++i)
            element[i].resize(n, 0);
    }

    Matrix operator *(Matrix a) {
        assert(n == a.n);
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ll tmp = 0;
                for (int k = 0; k < n; ++k) {
                    tmp += element[i][k] * a.element[k][j] % mod;
                    tmp %= mod;
                }
                res.element[i][j] = tmp;
            }
        }
        return res;
    }

    Matrix pow(ll k) {
        if (k == 0) {
            Matrix res(n);
            for (int i = 0; i < n; ++i)
                res.element[i][i] = 1;
            return res;
        }
        Matrix tmp = pow(k / 2);
        if (k % 2 == 1)
            return tmp * tmp * (*this);
        return tmp * tmp;
    }

	ll determinant() {
		vector<vector<ll>> b(n, vector<ll>(n));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				b[i][j] = element[i][j];
		ll res = 1;
		for (int i = 0; i < n; ++i) {
			int idx = -1;
			for (int j = i; j < n; ++j)
				if (b[j][i] != 0)
					idx = j;
			if (idx == -1) return 0;
			if (i != idx) {
				res *= -1; swap(b[i], b[idx]);
			}
			res = res * b[i][i] % mod;
			const ll inv = inverse(b[i][i]);
			for (int j = i + 1; j < n; ++j) {
				ll buf = b[j][i] * inv % mod;
				for (int k = 0; k < n; ++k)
					b[j][k] = (b[j][k] - b[i][k] * buf % mod + mod) % mod;
			}
		}
		return res;
	}
};