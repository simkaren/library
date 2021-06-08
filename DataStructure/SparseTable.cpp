// 検証済み(http://codeforces.com/contest/689/submission/70767796)

#include <bits/stdc++.h>

/* Sparse Tableを利用したRangeMinimumQuery */
template <typename T>
struct RMinQ_SparseTable {
private:
	// log_table : logの値
	// table[i][k] : インデックスiから長さ1<<kの最小値のインデックス
	std::vector<int> log_table;
	std::vector<std::vector<int>> table;
public:
	// n : 要素数
	// element : 要素
	int n;
	std::vector<T> element;
	// コンストラクタ
	RMinQ_SparseTable(const std::vector<T>& vec) {
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
	std::vector<int> log_table;
	std::vector<vector<int>> table;
public:
	// n : 要素数
	// element : 要素
	int n;
	std::vector<T> element;
	// コンストラクタ
	RMaxQ_SparseTable(const std::vector<T>& vec) {
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