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
		if (idx == 0) return {t, &t->data};
		auto p = mutable_get(
			t->children[idx & ((1 << LOG) - 1)],
			idx >> LOG
		);
		t->children[idx & ((1 << LOG) - 1)] = p.first;
		return { t, p.second };
	}
public:
	unsigned int size;
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

using namespace std;

int main(void) {
	PersistentArray<int> a(6);
	for (int i = 0; i < a.size; ++i)
		cout << a.get(i) << " "; // 0 0 0 0 0 0
	cout << endl;
	PersistentArray<int> b = a.update(3, 10);
	for (int i = 0; i < b.size; ++i)
		cout << b.get(i) << " "; // 0 0 0 10 0 0
	cout << endl; 
	for (int i = 0; i < a.size; ++i)
		cout << a.get(i) << " "; // 0 0 0 0 0 0
	cout << endl;
	b = b.update(5, 114514);
	a = a.update(0, 25252);
	for (int i = 0; i < b.size; ++i)
		cout << b.get(i) << " "; // 0 0 0 10 0 114514
	cout << endl;
	for (int i = 0; i < a.size; ++i)
		cout << a.get(i) << " "; // 25252 0 0 0 0 0
	cout << endl;
	PersistentArray<int> c = b.update(0, 334);
	c = c.update(1, 810);
	for (int i = 0; i < c.size; ++i)
		cout << c.get(i) << " "; // 334 810 0 10 0 114514
	cout << endl;
	return 0;
}