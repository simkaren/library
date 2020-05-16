// クエリ先読みができるとき、登場する座標を先に与えておくことで、
// 区間和取得の2Dセグ木ができる
// 座標の与え方は、
//      vector<vector<int>> idx
// で、
//      idx[x] : xのところのy座標

// 【注意】　未検証

#include <bits/stdc++.h>

using namespace std;

#define ll long long

template<typename T>
struct SegmentTree {
private:
	int sz, n;
	vector<T> data;
	function<T(T, T)> f;
	T identity_element;
public:
	/* constructor */
	SegmentTree() {}
	SegmentTree(
		vector<T> v, // initial data
		T identity_element, // identity element
		function<T(T, T)> f // operation
	) {
		sz = v.size();
		n = 1; while (n < sz) n <<= 1;
		this->f = f;
		this->identity_element = identity_element;
		data.resize(2 * n - 1, identity_element);
		for (int i = 0; i < sz; ++i)
			data[i + n - 1] = v[i];
		for (int i = n - 2; i >= 0; --i)
			data[i] = f(data[2 * i + 1], data[2 * i + 2]);
	}
	/* update query */
	void update(int idx, const T val) {
		idx += n - 1;
		data[idx] = val;
		while (idx) {
			idx = (idx - 1) >> 1;
			data[idx] = f(data[2 * idx + 1], data[2 * idx + 2]);
		}
	}
	/* get query */
	T get(int left, int right, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		if (r <= left || right <= l) return identity_element;
		if (left <= l && r <= right) return data[k];
		T val_l = get(left, right, 2 * k + 1, l, (l + r) / 2);
		T val_r = get(left, right, 2 * k + 2, (l + r) / 2, r);
		return f(val_l, val_r);
	}
};

struct SegmentTree2D {
	int NV;
	vector<SegmentTree<ll>> st;
	vector<vector<int>> idx;

	void init(vector<vector<int>>& v) {
		int n = v.size();
		NV = 1; while (NV < n) NV <<= 1;
		idx.resize(2 * NV);
		for (int i = 0; i < n; ++i)
			for (auto j : v[i])
				idx[i + NV].push_back(j);
		for (int i = NV * 2 - 1; i >= 1; --i) {
			sort(idx[i].begin(), idx[i].end());
			idx[i].erase(unique(idx[i].begin(), idx[i].end()), idx[i].end());
			for (auto j : idx[i])
				idx[i / 2].push_back(j);
		}
		st.resize(2 * NV);
		for (int i = 1; i < NV * 2; ++i)
			st[i] = SegmentTree<ll>(
				vector<ll>(idx[i].size(), 0LL), 0LL,
				[](ll a, ll b) { return a + b; }
		);
	}
	void update(int x, int y, ll v) {
		x += NV;
		while (x) {
			int yy = lower_bound(idx[x].begin(), idx[x].end(), y) - idx[x].begin();
			st[x].update(yy, v);
			x >>= 1;
		}
	}
	ll get(int sx, int tx, int sy, int ty, int k, int l, int r) {
		assert(k < NV * 2);
		assert(l < r);
		if (r <= sx or tx <= l) return 0;
		if (sx <= l and r <= tx) {
			int syy = lower_bound(idx[k].begin(), idx[k].end(), sy) - idx[k].begin();
			int tyy = lower_bound(idx[k].begin(), idx[k].end(), ty) - idx[k].begin();
			return st[k].get(syy, tyy);
		}
		int md = (l + r) / 2;
		ll le = get(sx, tx, sy, ty, k * 2, l, md);
		ll ri = get(sx, tx, sy, ty, k * 2 + 1, md, r);
		return le + ri;
	}
	ll get(int sx, int tx, int sy, int ty) {
		return get(sx, tx, sy, ty, 1, 0, NV);
	}
};