// 検証済み(http://codeforces.com/contest/689/submission/70767796)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

/* Sparse Tableを利用したRangeMinimumQuery */
template <typename T>
struct RMinQ_SparseTable {
private:
	// log_table : logの値
	// table[i][k] : インデックスiから長さ1<<kの最小値のインデックス
	vector<int> log_table;
	vector<vector<int>> table;
public:
	// n : 要素数
	// element : 要素
	int n;
	vector<T> element;
	// コンストラクタ
	RMinQ_SparseTable(vector<T> vec) {
		n = vec.size();
		element.resize(n);
		for (int i = 0; i < n; ++i)
			element[i] = vec[i];
		// log_tableを構築
		log_table.resize(n + 1, 0);
		for (int i = 2; i <= n; ++i)
			log_table[i] = log_table[i >> 1] + 1;
		// tableを構築
		table.resize(n, vector<int>(log_table[n] + 1));
		for (int i = 0; i < n; ++i)
			table[i][0] = i;
		for (int k = 1; (1 << k) <= n; ++k) {
			for (int i = 0; i + (1 << k) <= n; ++i) {
				int c1 = table[i][k - 1], c2 = table[i + (1 << (k - 1))][k - 1];
				if (element[c1] < element[c2]) table[i][k] = c1;
				else table[i][k] = c2;
			}
		}
	}
	// [l, r)の範囲の最小値のインデックスを求める
	int query_idx(int l, int r) {
		int d = r - l;
		int k = log_table[d];
		if (element[table[l][k]] < element[table[r - (1 << k)][k]])
			return table[l][k];
		return table[r - (1 << k)][k];
	}
	// [l,r)の範囲の最小値を求める
	T query_value(int l, int r) {
		return element[query_idx(l, r)];
	}
};

/* Sparse Tableを利用したRangeMaximumQuery */
template <typename T>
struct RMaxQ_SparseTable {
private:
	// log_table : logの値
	// table[i][k] : インデックスiから長さ1<<kの最大値のインデックス
	vector<int> log_table;
	vector<vector<int>> table;
public:
	// n : 要素数
	// element : 要素
	int n;
	vector<T> element;
	// コンストラクタ
	RMaxQ_SparseTable(vector<T> vec) {
		n = vec.size();
		element.resize(n);
		for (int i = 0; i < n; ++i)
			element[i] = vec[i];
		// log_tableを構築
		log_table.resize(n + 1, 0);
		for (int i = 2; i <= n; ++i)
			log_table[i] = log_table[i >> 1] + 1;
		// tableを構築
		table.resize(n, vector<int>(log_table[n] + 1));
		for (int i = 0; i < n; ++i)
			table[i][0] = i;
		for (int k = 1; (1 << k) <= n; ++k) {
			for (int i = 0; i + (1 << k) <= n; ++i) {
				int c1 = table[i][k - 1], c2 = table[i + (1 << (k - 1))][k - 1];
				if (element[c1] < element[c2]) table[i][k] = c2;
				else table[i][k] = c1;
			}
		}
	}
	// [l, r)の範囲の最大値のインデックスを求める
	int query_idx(int l, int r) {
		int d = r - l;
		int k = log_table[d];
		if (element[table[l][k]] < element[table[r - (1 << k)][k]])
			return  table[r - (1 << k)][k];
		return table[l][k];
	}
	// [l, r)の範囲の最大値のインデックスを求める
	T query_value(int l, int r) {
		return element[query_idx(l, r)];
	}
};

int main() {
	// 入力受け取り
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	// SparseTableの構築
	RMaxQ_SparseTable<int> a_table(a);
	RMinQ_SparseTable<int> b_table(b);
	// 左端lについて、okな右端rの範囲を求める
	ll res = 0;
	for (int l = 0; l < n; ++l) {
		if (a[l] > b[l]) continue;
		if (a_table.query_value(l, n) < b_table.query_value(l, n)) break;
		// r_min : max a[l:i] < min b[l:i]なる最大のi
		int r_min = l, r_min_ng = n + 1;
		while (r_min_ng - r_min > 1) {
			int mid = (r_min + r_min_ng) / 2;
			if (a_table.query_value(l, mid) < b_table.query_value(l, mid))
				r_min = mid;
			else r_min_ng = mid;
		}
		// r_max : max a[l:i] <= min b[l:i]なる最大のi
		int r_max = l, r_max_ng = n + 1;
		while (r_max_ng - r_max > 1) {
			int mid = (r_max + r_max_ng) / 2;
			if (a_table.query_value(l, mid) <= b_table.query_value(l, mid))
				r_max = mid;
			else r_max_ng = mid;
		}
		res += (ll)r_max - r_min;
	}
	cout << res << endl;
	return 0;
}