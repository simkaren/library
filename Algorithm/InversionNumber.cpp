#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>

template<typename T>
struct SegmentTree {
private:
	int sz, n;
	std::vector<T> data;
	std::function<T(T, T)> f;
	T identity_element;
public:
	/* constructor */
	SegmentTree(
		const std::vector<T>& v, // initial data
		T identity_element, // identity element
		std::function<T(T, T)> f // operation
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

long long _invertion_number(int max_v, std::vector<int>& v){
	SegmentTree<int> seg(std::vector<int>(max_v + 1, 0), 0, [](int l, int r){ return l + r; });
	long long ret = 0;
	for (int& vi : v){
		ret += seg.get(vi + 1, max_v + 1);
		int tmp = seg.get(vi, vi + 1);
		seg.update(vi, tmp + 1);
	}
	return ret;
}

template<typename T>
long long inversion_number(std::vector<T>& v){
	std::map<T, int> compress;
	for (auto& vi : v)
		compress[vi];
	int t = 0;
	for (auto& e : compress)
		e.second = t++;
	std::vector<int> compressed_v(v.size());
	for (int i = 0; i < (int)v.size(); ++i)
		compressed_v[i] = compress[v[i]];
	return _invertion_number(t - 1, compressed_v);
}
