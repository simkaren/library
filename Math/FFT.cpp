// 検証済み(https://atcoder.jp/contests/atc001/submissions/7805997)

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

// DFTをFFTで求める.
vector<complex<double>> dft(vector<complex<double>> a, int n, int sgn = 1) {
	const double two_pi = 2 * 3.141592653589793;
	if (n == 1) return a;
	vector<complex<double>> f(n / 2), g(n / 2);
	for (int i = 0; i < n / 2; ++i) {
		f[i] = a[2 * i]; g[i] = a[2 * i + 1];
	}
	f = dft(f, n / 2, sgn); g = dft(g, n / 2, sgn);
	const complex<double> z = complex<double>(cos(two_pi / n), -sin(two_pi / n) * sgn);
	complex<double> tmp = 1;
	for (int i = 0; i < n / 2; ++i) {
		a[i] = f[i] + tmp * g[i];
		tmp *= z;
	}
	for (int i = n / 2; i < n; ++i) {
		a[i] = f[i - (n / 2)] + tmp * g[i - (n / 2)];
		tmp *= z;
	}
	return a;
}

// 逆DFTを行う.
vector<complex<double>> inv_dft(vector<complex<double>> a, int n) {
	a = dft(a, n, -1);
	for (int i = 0; i < n; ++i)
		a[i] /= n;
	return a;
}

// aとbの畳み込みを行う.
vector<complex<double>> convolution(vector<complex<double>> a, vector<complex<double>> b) {
	int n = 1;
	const int need = a.size() + b.size() - 1;
	while (n < need) n *= 2;
  
	a.resize(n); b.resize(n);
	a = dft(a, n); b = dft(b, n);

	vector<complex<double>> f(n);
	for (int i = 0; i < n; ++i)
		f[i] = a[i] * b[i];
	f = inv_dft(f, n);
	return f;
}


signed main() {
	int n; cin >> n;
	vector<complex<double>> a(n + 1, 0), b(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		int ai, bi;
		cin >> ai >> bi;
		a[i] = complex<double>(ai);
		b[i] = complex<double>(bi);
	}

	auto conv = convolution(a, b);

	for (int k = 1; k <= 2 * n; ++k) {
		int res = (int)(conv[k].real() + 0.5);
		cout << res << endl;
	}

	return 0;
}
