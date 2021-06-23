// 検証済み(https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5605574)

#include <bits/stdc++.h>

template<typename T>
struct WarshallFloyd {
private:
	const T INF = std::numeric_limits<T>::max();
	int n;
	std::vector<std::vector<T>> g;
	bool built = false;
	bool hasNegCycle = false;
	void _build(void){
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (g[i][k] != INF && g[k][j] != INF)
						g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
	}
public:
	/* constructor */
	WarshallFloyd(int n) {
		this->n = n;
		g.resize(n, std::vector<T>(n, INF));
		for (int i = 0; i < n; ++i)
			g[i][i] = (T)0;
	}
	/* add edge i --> j */
	void add_edge(int i, int j, T cost, bool directed = false) {
		g[i][j] = cost;
		if (!directed)
			g[j][i] = cost;
	}
	/* build */
	void build(void) {
		_build();
		auto g_save = g;
		_build();
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (g[i][j] != g_save[i][j]){
					hasNegCycle = true;
					goto FIN;
				}
			}
		}
		FIN:;
		built = true;
	}
	/* get dist */
	T get_dist(int i, int j){
		assert(built);
		return g[i][j];
	}
	/* graph has negative cycle? */
	bool has_neg_cycle(void){
		assert(built);
		return hasNegCycle;
	}
};