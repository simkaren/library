#include <bits/stdc++.h>

using namespace std;

#define ld long double

/* 幾何ライブラリ */

// 定数
constexpr ld PI = 3.14159265358979323846L;
constexpr ld PI_2 = 2 * PI;
const ld EPS = 1e-12L; // 誤差

// 2次元座標, 2次元ベクトル
using pos = pair<ld, ld>;

// 加算
pos add(pos p1, pos p2) {
	return { p1.first + p2.first, p1.second + p2.second };
}
// 減算
pos sub(pos p1, pos p2) {
	return { p1.first - p2.first, p1.second - p2.second };
}
// 内積
ld inner_product(pos p1, pos p2) {
	return p1.first * p2.first + p1.second * p2.second;
}
// 定数倍
pos mul(ld c, pos p) {
	return { c * p.first, c * p.second };
}

// ノルムの2乗
ld norm2(pos p) {
	return p.first * p.first + p.second * p.second;
}
// ノルム
ld norm(pos p) {
	return sqrt(norm2(p));
}

// 平行判定
bool is_parallel(pos v1, pos v2) {
	return abs(v1.first * v2.second - v1.second * v2.first) < EPS;
}
// 直行判定
bool is_orthogonal(pos v1, pos v2) {
	return abs(inner_product(v1, v2)) < EPS;
}

// 射影
// pをp1, p2を通る直線に射影する
// 検証済み(https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_A)
pos projection(pos p1, pos p2, pos p) {
	pos q = sub(p2, p1);
	pos tmp = mul(inner_product(q, sub(p, p1)) / norm2(q), q);
	return add(p1, tmp);
}

// 反射
// pをp1, p2を通る直線に関して対称移動する
// 検証済み(https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_B)
pos reflection(pos p1, pos p2, pos p) {
	pos tmp = projection(p1, p2, p);
	return add(p, mul(2.0, sub(tmp, p)));
}

// 位置関係
// p0を基準に、p1, p2の位置関係を求める
// p2が
//	p1から反時計回り方向 : COUNTER_CLOCKWISE
//	p1から時計回り方向 : CLOCKWISE
//	p1と反対方向(p2, p0, p1がこの順に同一直線上) : ONLINE_BACK
//	p1の延長線上(p0, p1, p2がこの順に同一直線上) : ONLINE_FRONT
//	p1の途中(線分p0p1の上) : ON_SEGMENT
// 検証済み(https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_C)
string positional_relation(pos p0, pos p1, pos p2) {
	pos v1 = sub(p1, p0), v2 = sub(p2, p0);
	if (abs(v2.first) < EPS && abs(v2.second) < EPS) return "ON_SEGMENT";
	ld r1 = atan2l(v1.second, v1.first), r2 = atan2l(v2.second, v2.first);
	if (abs(r1 - r2) < EPS || (abs(r1 - r2) > PI - EPS && abs(r1 - r2) < PI + EPS)) { // ONLINE
		if (v1.first * v2.first < 0 || v1.second * v2.second < 0)
			return "ONLINE_BACK";
		if (abs(v1.first) < abs(v2.first) || abs(v1.second) < abs(v2.second))
			return "ONLINE_FRONT";
		return "ON_SEGMENT";
	}
	// NOT ONLINE
	if (r2 - r1 + (r2 - r1 < 0 ? PI_2 : 0) < PI)
		return "COUNTER_CLOCKWISE";
	return "CLOCKWISE";
}

// 線分の交差判定
// 線分p0p1, q0q1が交叉するか、端点を含むかどうかは最後の引数(デフォルトは有効)
// 検証済み(https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_2_B)
bool cross(pos p0, pos p1, pos q0, pos q1, bool end_point = true) {
	ld ta = (q0.first - q1.first) * (p0.second - q0.second)
		+ (q0.second - q1.second) * (q0.first - p0.first);
	ld tb = (q0.first - q1.first) * (p1.second - q0.second)
		+ (q0.second - q1.second) * (q0.first - p1.first);
	ld tc = (p0.first - p1.first) * (q0.second - p0.second)
		+ (p0.second - p1.second) * (p0.first - q0.first);
	ld td = (p0.first - p1.first) * (q1.second - p0.second)
		+ (p0.second - p1.second) * (p0.first - q1.first);
	if (tc * td < -EPS && ta * tb < -EPS) return true;
	else if (!end_point) return false;
	if (positional_relation(p0, p1, q0) == "ON_SEGMENT"
		|| positional_relation(p0, p1, q1) == "ON_SEGMENT")
		return true;
	if (positional_relation(q0, q1, p0) == "ON_SEGMENT"
		|| positional_relation(q0, q1, p1) == "ON_SEGMENT")
		return true;
	return false;
}

int main() {
	int q; cin >> q;
	while (q--) {
		pos p0, p1, p2, p3;
		cin >> p0.first >> p0.second;
		cin >> p1.first >> p1.second;
		cin >> p2.first >> p2.second;
		cin >> p3.first >> p3.second;
		bool f = cross(p0,p1,p2,p3);
		cout << (f ? 1 : 0) << endl;
	}
	return 0;
}