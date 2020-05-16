// 検証済み(https://www.spoj.com/status/ns=24508678)

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

// Mo's algorithm (Query Square Root Decomposition)
struct Mo {
private:
	// 要素数nとその平方根width
	int n, width;
	// データが含まれているかを表すフラグ
	vector<bool> v;
	// クエリ
	struct query {
		int id; // クエリのid
		int l, r; // クエリの対象区間[l,r)
		query(int id, int l, int r) : id(id), l(l), r(r) {}
	};
	vector<query> q;
	// data[idx] を処理
	void distribute(int idx) {
		if (v[idx]) del(idx);
		else add(idx);
		v[idx].flip();
	}
public:
	// コンストラクタ(引数はデータ)
	Mo(int n) : width((int)sqrt(n)), n(n), v(n, false) {}
	// クエリの追加
	void add_query(int l, int r) {
		int id = q.size();
		query new_q(id, l, r);
		q.push_back(new_q);
	}
	// クエリのソート
	void build() {
		sort(
			q.begin(), q.end(),
			[&](query a, query b) {
				if (a.l / width != b.l / width)
					return a.l < b.l;
				return a.r < b.r;
			}
		);
	}
	// data[idx]が区間に追加されるときの処理
	void add(int idx) {
		// TODO
	}
	// data[idx]が区間から削除されるときの処理
	void del(int idx) {
		// TODO
	}
	// クエリを一つ処理する(処理したクエリのidが返される)
	int process() {
		static int ptr = 0;
		static int nl = 0, nr = 0;
		if (ptr == q.size()) return -1;
		while (nl > q[ptr].l) distribute(--nl);
		while (nr < q[ptr].r) distribute(nr++);
		while (nl < q[ptr].l) distribute(nl++);
		while (nr > q[ptr].r) distribute(--nr);
		return (q[ptr++].id);
	}
};