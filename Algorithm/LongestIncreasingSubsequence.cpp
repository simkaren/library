#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct SegmentTree {
private:
	int sz, n;
	vector<T> data;
	function<T(T, T)> f;
	T identity_element;
public:
	/* constructor */
	SegmentTree(
		vector<T> v, // initial data
		T identity_element, // identity element
		function<T(T, T)> f // operation
	) {
		sz = v.size();
		n = 1; while (n < sz) n <<= 1;
		this->f = f;
		this->identity_element = identity_element;
		data.resize(2 * n - 1, identity_element);
		for (int i = 0; i < sz; ++i)
			data[i + n - 1] = v[i];
		for (int i = n - 2; i >= 0; --i)
			data[i] = f(data[2 * i + 1], data[2 * i + 2]);
	}
	/* update query */
	void update(int idx, const T val) {
		idx += n - 1;
		data[idx] = val;
		while (idx) {
			idx = (idx - 1) >> 1;
			data[idx] = f(data[2 * idx + 1], data[2 * idx + 2]);
		}
	}
	/* get query */
	T get(int left, int right, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		if (r <= left || right <= l) return identity_element;
		if (left <= l && r <= right) return data[k];
		T val_l = get(left, right, 2 * k + 1, l, (l + r) / 2);
		T val_r = get(left, right, 2 * k + 2, (l + r) / 2, r);
		return f(val_l, val_r);
	}
};

template<typename T>
int LIS(vector<T>& a){
    map<T, int> com;
    for (auto ai : a) com[ai];
    int t = 0;
    for (auto& e : com)
        e.second = t++;
    SegmentTree<int> seg(
        vector<int>(com.size(), 0), 0,
        [](int x, int y) { return max(x, y); }
    );
    for (auto ai : a){
        int v = com[ai];
        seg.update(v, seg.get(0, v) + 1);
    }
    return seg.get(0, com.size());
}