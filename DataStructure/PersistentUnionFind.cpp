// 検証済み(https://judge.yosupo.jp/submission/19257)

#include <bits/stdc++.h>

template<typename T, int LOG = 4>
struct PersistentArray {
	struct node {
		T data;
		node* children[1 << LOG] = {};
		node(void) : data() {}
		node(T& data) : data(data) {}
	};
private:
	node* root = nullptr;
	node* build(node* t, const T& data, int idx) {
		if (!t) t = new node();
		if (idx == 0) {
			t->data = data;
			return t;
		}
		node* p = build(
			t->children[idx & ((1 << LOG) - 1)],
			data, idx >> LOG
		);
		t->children[idx & ((1 << LOG) - 1)] = p;
		return t;
	}
	T get(node* t, int idx) {
		if (idx == 0) return t->data;
		T res = get(
			t->children[idx & ((1 << LOG) - 1)],
			idx >> LOG
		);
		return res;
	}
	std::pair<node*, T*> mutable_get(node* t, int idx) {
		t = t ? new node(*t) : new node();
		if (idx == 0) return { t, &t->data };
		auto p = mutable_get(
			t->children[idx & ((1 << LOG) - 1)],
			idx >> LOG
		);
		t->children[idx & ((1 << LOG) - 1)] = p.first;
		return { t, p.second };
	}
public:
	unsigned int size;
	PersistentArray() {}
	PersistentArray(const vector<T>& v) {
		size = v.size();
		for (int i = 0; i < (int)size; ++i)
			root = build(root, v[i], i);
	}
	PersistentArray(int size) {
		assert(("Array size must not be negative.", size >= 0));
		this->size = (unsigned int)size;
		T def = T();
		for (int i = 0; i < size; ++i)
			root = build(root, def, i);
	}
	PersistentArray(node* root, unsigned int size) :
		root(root), size(size) {}
	T get(const int& idx) {
		assert(("Index is out of range.", 0 <= idx && idx < (int)size));
		return get(root, idx);
	}
	PersistentArray update(int idx, const T& data) {
		assert(("Index is out of range.", 0 <= idx && idx < (int)size));
		auto tmp = mutable_get(root, idx);
		*(tmp.second) = data;
		return PersistentArray(tmp.first, size);
	}
};

struct PersistentUnionFind {
	map<int, PersistentArray<int>> data;
	// 頂点数nの初期グラフを生成(-1番目とする)
	PersistentUnionFind(int n) {
		PersistentArray<int> init(vector<int>(n, -1));
		data[-1] = init;
	}
	// t番目のグラフでのkの集合
	int find(int t, int k) {
		int tmp = data[t].get(k);
		if (tmp < 0) return k;
		return find(t, tmp);
	}
	// t番目のグラフでunite(x, y)をしたものをidx番とする
	bool unite(int t, int x, int y, int idx) {
		PersistentArray<int> tmp = data[t];
		x = find(t, x);
		y = find(t, y);
		if (x == y) {
			data[idx] = tmp;
			return false;
		}
		int dx = tmp.get(x), dy = tmp.get(y);
		if (dx > dy) swap(x, y);
		PersistentArray<int> new_data = tmp.update(x, dx + dy);
		new_data = new_data.update(y, x);
		data[idx] = new_data;
		return true;
	}
	// t番目のグラフでaとbは同じ集合に属すか
	bool same(int t, int a, int b) {
		return (find(t, a) == find(t, b));
	}
	// t番目のグラフでkの属する集合のサイズ
	int size(int t, int k) {
		return -data[t].get(find(t, k));
	}
};

using namespace std;

int main(void) {
	int N, Q; cin >> N >> Q;
	PersistentUnionFind puf(N);
	for (int i = 0; i < Q; ++i) {
		int c, k, u, v;
		cin >> c >> k >> u >> v;
		if (c == 0) { // unite
			(void)puf.unite(k, u, v, i);
		}
		else { // same
			if (puf.same(k, u, v)) cout << 1 << endl;
			else cout << 0 << endl;
		}
	}
	return 0;
}