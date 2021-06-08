#include <bits/stdc++.h>

// Mo's algorithm (Query Square Root Decomposition)
struct Mo {
private:
	// n : the number of element, width : sqrt(n)
	int n, width;
	// whether the data is in or out
	std::vector<bool> v;
	// query
	struct query {
		int id;
		int l, r;
		query(int id, int l, int r) : id(id), l(l), r(r) {}
	};
	std::vector<query> q;
	// process data[idx]
	void distribute(int idx) {
		if (v[idx]) del(idx);
		else add(idx);
		v[idx].flip();
	}
public:
	Mo(int n) : width((int)sqrt(n)), n(n), v(n, false) {}
	void add_query(int l, int r) {
		int id = q.size();
		query new_q(id, l, r);
		q.push_back(new_q);
	}
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
	// process one query (returns the id of the query)
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