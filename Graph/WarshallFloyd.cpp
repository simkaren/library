// 検証済み(http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4113717#1)

#include <bits/stdc++.h>

using namespace std;

#define ll long long

template<typename T>
struct WarshallFloyd {
	const T INF = numeric_limits<T>::max();
	int n;
	vector<vector<T>> g;
	/* コンストラクタ */
	// n : 頂点数
	WarshallFloyd(int n) {
		this->n = n;
		g.resize(n, vector<T>(n, INF));
		for (int i = 0; i < n; ++i)
			g[i][i] = (T)0;
	}
	/* 辺を張る */
	// iからjに辺を張る、fが0以外の時は有向辺、0なら無向辺
	void add_edge(int i, int j, T cost, int f = 0) {
		g[i][j] = cost;
		if (f == 0)
			g[j][i] = cost;
	}
	/* Warshall-Floyd法により全点対間最短距離を求め、gを更新 */
	void calc() {
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (g[i][k] != INF && g[k][j] != INF)
						g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	}
};

int main() {
	int v, e; cin >> v >> e;
	WarshallFloyd<ll> wf(v);
	while (e--) {
		int s, t; ll d;
		cin >> s >> t >> d;
		wf.add_edge(s, t, d, 1);
	}
	wf.calc();
	// 負閉路の検出のためにもう一度WFする
	WarshallFloyd<ll> tmp = wf;
	tmp.calc();
	// 負閉路の判定
	for (int i = 0; i < v; ++i) {
		for (int j = 0; j < v; ++j) {
			if (wf.g[i][j] != tmp.g[i][j]) {
				cout << "NEGATIVE CYCLE" << endl;
				goto END;
			}
		}
	}
	// そうでない場合
	for (int i = 0; i < v; ++i) {
		for (int j = 0; j < v; ++j) {
			if (wf.g[i][j] != wf.INF) cout << wf.g[i][j];
			else cout << "INF";
			if (j != v - 1) cout << " ";
		}
		cout << endl;
	}
END:;
	return 0;
}