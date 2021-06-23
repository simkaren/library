// 検証済み(https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5605513)

#include <bits/stdc++.h>

struct LCA {
private:
	int n, LOG_N;
	std::vector<std::vector<int>> G;
	std::vector<int> par;
	std::vector<int> dep;
	std::vector<std::vector<int>> table;

	/* construct par and dep by dfs */
	void dfs(int s = 0, int p = 0, int d = 0) {
		static std::vector<bool> visited;
		visited.resize(n, false);
		visited[s] = true;
		par[s] = p; dep[s] = d;
		for (auto nx : G[s])
			if (!visited[nx])
				dfs(nx, s, d + 1);
	}

public:
	/* constructor */
	LCA(std::vector<std::vector<int>>& G) {
		n = G.size();
		this->G = G;
		par.resize(n);
		dep.resize(n, 0);
		int tmp = n; LOG_N = 1;
		while (tmp) {
			tmp >>= 1;
			++LOG_N;
		}
		table.resize(n, std::vector<int>(LOG_N, -1));
		dfs();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < LOG_N; ++j)
				table[i][j] = par[i];
		for (int j = 1; j < LOG_N; ++j)
			for (int i = 0; i < n; ++i)
				table[i][j] = table[table[i][j - 1]][j - 1];
	}
	/* find LCA of u and v */
	int find_LCA(int u, int v) {
		if (dep[u] > dep[v]) std::swap(u, v);
		for (int i = LOG_N - 1; i >= 0; --i)
			if ((dep[v] - dep[u]) & (1 << i))
				v = table[v][i];
		if (u == v) return u;
		for (int i = LOG_N - 1; i >= 0; --i) {
			if (table[u][i] != table[v][i]) {
				u = table[u][i]; v = table[v][i];
			}
		}
		return table[u][0];
	}
};