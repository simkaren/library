// 検証済み(http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4556352#1)

#include <bits/stdc++.h>

template<typename T>
struct Graph {
	struct edge {
		int to, rev;
		T cap;
		edge(int to, int rev, T cap) : to(to), rev(rev), cap(cap) {}
	};
private:
	int n;
	std::vector<std::vector<edge>> g;
	std::vector<bool> used;

	T dfs(int v, int t, T f) {
		if (v == t) return f;
		used[v] = true;
		for (int i = 0; i < g[v].size(); ++i) {
			edge& e = g[v][i];
			if (!used[e.to] && e.cap > 0) {
				T d = dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					g[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return (T)0;
	}

public:
	Graph(int n) : n(n), g(n) {}

	void add_edge(int from, int to, T cap) {
		g[from].push_back(edge(to, (int)g[to].size(), cap));
		g[to].push_back(edge(from, (int)g[from].size() - 1, (T)0));
	}

	T max_flow(int s, int t) {
		T res = 0;
		while (1) {
			used = std::vector<bool>(n, false);
			T tmp = dfs(s, t, std::numeric_limits<T>::max());
			if (tmp == 0) break;
			res += tmp;
		}
		return res;
	}
};