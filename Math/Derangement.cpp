#include <bits/stdc++.h>

using namespace std;

constexpr ll mod = 1000000007LL;

// 攪乱順列の個数を計算する
ll derangement(int n) {
	static vector<ll> res{ 0, 0, 1, 2 };
	while (n >= (int)(res.size())) {
		const int sz = res.size();
		res.push_back((sz - 1LL) * ((res[sz - 1] + res[sz - 2]) % mod) % mod);
	}
	return res[n];
}
