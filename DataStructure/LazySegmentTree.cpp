#include <bits/stdc++.h>

struct LazySegmentTree {
private:
	int n; // length of node, lazy
	std::vector<long long> node, lazy;
	/* propagete the laziness of the k-th node. */
	void eval(int k, int l, int r) {
		if (lazy[k] != 0) {
			node[k] += lazy[k];
			if (r - l > 1) {
				lazy[2 * k + 1] += lazy[k] / 2;
				lazy[2 * k + 2] += lazy[k] / 2;
			}
			lazy[k] = 0;
		}
	}
public:
	/* constructor. v is the data. */
	LazySegmentTree(const std::vector<long long>& v) {
		int sz = (int)v.size();
		n = 1; while (n < sz) n *= 2;
		node.resize(2 * n - 1);
		lazy.resize(2 * n - 1, 0);
		for (int i = 0; i < sz; i++) node[i + n - 1] = v[i];
		for (int i = n - 2; i >= 0; i--) node[i] = node[i * 2 + 1] + node[i * 2 + 2];
	}
	/* add x to s[a],s[a+1],...,s[b-1] */
	void add(int a, int b, long long x, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] += (r - l) * x;
			eval(k, l, r);
		}
		else {
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = node[2 * k + 1] + node[2 * k + 2];
		}
	}
	/* calculate the sum of s[a],s[a+1],...,s[b-1] */
	long long getsum(int a, int b, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		long long vl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
		long long vr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
		return vl + vr;
	}
};

constexpr long long mod = 1000000007LL;
constexpr long long div2 = 500000004LL;

struct ModLazySegmentTree {
private:
	int n; // length of node, lazy
	std::vector<long long> node, lazy;
	/* propagete the laziness of the k-th node. */
	void eval(int k, int l, int r) {
		if (lazy[k] != 0) {
			node[k] = (node[k] + lazy[k]) % mod;
			if (r - l > 1) {
				lazy[2 * k + 1] = (lazy[2 * k + 1] + lazy[k] * div2 % mod) % mod;
				lazy[2 * k + 2] = (lazy[2 * k + 2] + lazy[k] * div2 % mod) % mod;
			}
			lazy[k] = 0;
		}
	}
public:
	/* constructor. v is the data. */
	ModLazySegmentTree(const std::vector<long long>& v) {
		int sz = (int)v.size();
		n = 1; while (n < sz) n *= 2;
		node.resize(2 * n - 1);
		lazy.resize(2 * n - 1, 0);
		for (int i = 0; i < sz; i++) node[i + n - 1] = v[i];
		for (int i = n - 2; i >= 0; i--)
			node[i] = (node[i * 2 + 1] + node[i * 2 + 2]) % mod;
	}
	/* add x to s[a],s[a+1],...,s[b-1] */
	void add(int a, int b, long long x, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] = (lazy[k] + (r - l) * x % mod) % mod;
			eval(k, l, r);
		}
		else {
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = (node[2 * k + 1] + node[2 * k + 2]) % mod;
		}
	}
	/* calculate the sum of s[a],s[a+1],...,s[b-1] */
	long long getsum(int a, int b, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		long long vl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
		long long vr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
		return (vl + vr) % mod;
	}
};