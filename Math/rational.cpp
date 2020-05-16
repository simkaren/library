#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll gcd(ll a, ll b){
    if (b > a) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 有理数を表す構造体
// 分母分子はlong longに収まる範囲でなければならない
// 演算子を使用する場合は、分母分子が1e9程度以下出なければならない
struct rational {
	// n : 分母
	// d : 分子
	ll n, d;
	// コンストラクタ
	rational(ll n, ll d) : n(n), d(d) {}
	// 約分
	void reduction() {
		ll g = gcd(abs(n), abs(d));
		n /= g; d /= g;
		if (n < 0) {
			n *= -1; g *= -1;
		}
	}
	// 表示
	void show() {
		// 分子,分母の順に半角スペース区切り
		if (n != 1)
			cout << d << " " << n << endl;
		else
			cout << d << endl;
	}
	// 符号反転
	rational operator -(){
		rational res(-this->n, this->d);
		return res;
	}
	// 掛け算
	rational operator *(rational r) {
		rational res(this->n * r.n, this->d * r.d);
		res.reduction();
		return res;
	}
	// 割り算
	rational operator /(rational r) {
		rational res(this->n * r.d, this->d * r.n);
		res.reduction();
		return res;
	}
	// 足し算
	rational operator +(rational r) {
		rational res(this->n * r.n, this->d * r.n + this->n * r.d);
		res.reduction();
		return res;
	}
	// 引き算
	rational operator -(rational r) {
		rational res(this->n * r.n, this->d * r.n - this->n * r.d);
		res.reduction();
		return res;
	}
};