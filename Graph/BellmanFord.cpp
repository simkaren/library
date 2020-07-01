// 検証済み(https://atcoder.jp/contests/abc137/submissions/14129913)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

template<typename T>
struct BellmanFord {
	struct edge {
		int u, v; T w;
		edge(int from, int to, T weight) {
			u = from;
			v = to;
			w = weight;
		}
	};

	int n; // 頂点数
	vector<vector<int>> G;
	vector<int> used, reach;
	BellmanFord(int n) : n(n), G(n), used(n, 0), reach(n, 0) {}

	vector<edge> es;
	void add_edge(int u, int v, T c) {
		es.emplace_back(u, v, c);
		G[u].emplace_back(v);
	}

	void dfs(int v) {
		if (used[v]) return;
		used[v] = 1;
		for (int u : G[v])
			dfs(u);
	}

	// fromからtoまでの最短経路を求める.
	// 負閉路がある場合にはneg_loopに1が格納される.
	T build(int from, int to, int& neg_loop) {
		for (int i = 0; i < n; i++) {
			fill(used.begin(), used.end(), 0);
			dfs(i);
			reach[i] = used[to];
		}
		const T INF = numeric_limits<T>::max();
		vector<T> ds(n, INF);
		ds[from] = 0;
		for (int j = 0; j < n; j++) {
			bool update = 0;
			for (auto e : es) {
				if (!reach[e.u] || !reach[e.v] || ds[e.u] == INF) continue;
				if (ds[e.v] > ds[e.u] + e.w) {
					ds[e.v] = ds[e.u] + e.w;
					update = 1;
				}
			}
			if (!update) break;
			if (j == n - 1) {
				neg_loop = 1;
				return INF;
			}
		}
		neg_loop = 0;
		return ds[to];
	}
};

signed main() {
	int n, m, p;
	cin >> n >> m >> p;
	BellmanFord<int> g(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		g.add_edge(a, b, p - c);
	}

	int neg;
	int res = g.build(1, n, neg);

	if (neg) cout << -1 << endl;
	else cout << max(0, -res) << endl;

	return 0;
}