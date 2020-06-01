// 検証済み(http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4536871#1)

#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

ld _closest_pair_of_points(vector<pair<ld, ld>>& ps, int l, int r){
    constexpr ld INF = 1e15L;
    constexpr ld eps = 1e-10L;
    if (r - l <= 1) return INF;
    const int m = (l + r) / 2;
    ld x_mid = ps[m].first;
    ld left_half = _closest_pair_of_points(ps, l, m);
    ld right_half = _closest_pair_of_points(ps, m, r);
    ld res = min(left_half, right_half);
    inplace_merge(
        ps.begin() + l, ps.begin() + m, ps.begin() + r, 
        [](const pair<ld, ld> a, const pair<ld, ld> b){
            return a.second < b.second;
        }
    );
    vector<int> idx;
    for (int i = l; i < r; ++i){
        if (abs(ps[i].first - x_mid) > res + eps)
            continue;
        for (int j = idx.size() - 1; j >= 0; --j){
            ld dx = ps[i].first - ps[idx[j]].first;
            ld dy = ps[i].second - ps[idx[j]].second;
            if (dy > res + eps) break;
            res = min(res, sqrtl(dx * dx + dy * dy));
        }
        idx.push_back(i);
    }
    return res;
}

ld closest_pair_of_points(vector<pair<ld, ld>> lis){
    sort(lis.begin(), lis.end());
    return _closest_pair_of_points(lis, 0, lis.size());
}

int main(void){
    int n; cin >> n;
    vector<pair<ld, ld>> lis(n);
    for (int i = 0; i < n; ++i)
        cin >> lis[i].first >> lis[i].second;
    cout << fixed << setprecision(15) << closest_pair_of_points(lis) << endl;
    return 0;
}