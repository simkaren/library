#include <bits/stdc++.h>

using namespace std;

#define ll long long

// modが素数でない場合、挙動がおかしくなる.
const ll mod = 1000000007LL;

// aのb乗を求める.
ll modpow(ll a, ll b) {
	if (a > mod) a %= mod;
	if (b == 0LL) return 1LL;
	ll tmp = modpow(a, b / 2);
	if (b & 1LL)
		return tmp * tmp % mod * a % mod;
	return tmp * tmp % mod;
}

// aの逆元を求める.
ll inverse(ll a) {
	return modpow(a, mod - 2);
}

// kの階乗を計算する.(sgnを0以外に設定すると逆元を返す)
ll fact(ll k, int sgn = 0) {
	static vector<ll> fac(2, 1LL);
	static vector<ll> inv(2, 1LL);
	static vector<ll> finv(2, 1LL);
	static ll nx = 2LL;
	while (nx <= k) {
		fac.push_back(fac[nx - 1] * nx % mod);
		inv.push_back(mod - inv[mod % nx] * (mod / nx) % mod);
		finv.push_back(finv[nx - 1] * inv[nx] % mod);
		++nx;
	}
	if (sgn == 0)
		return fac[k];
	return finv[k];
}

// aCbを計算する.
ll comb(ll a, ll b) {
	if (b < 0 || b > a) return 0;
	return fact(a) * fact(b, 1) % mod * fact(a - b, 1) % mod;
}
