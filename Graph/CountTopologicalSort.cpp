// 検証済み(https://atcoder.jp/contests/abc041/submissions/14107876)

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

ll cnt_topological_sort(vector<vector<int>>& g){
    const int n = g.size();
    assert(1 <= n && n <= 16);
    vector<int> bit_flg(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j : g[i])
            bit_flg[i] |= (1 << j);
    vector<ll> dp(1 << n, 0);
    dp[0] = 1;
    for (int i = 0; i < (1 << n); ++i)
        for (int j = 0; j < n; ++j)
            if ((i & (1 << j)) == 0 && (i & bit_flg[j]) == 0)
                dp[i | (1 << j)] += dp[i];
    return dp[(1 << n) - 1];
}

int main(void){
    int N, M; cin >> N >> M;
    vector<vector<int>> g(N);
    for (int i = 0; i < M; ++i){
        int x, y; cin >> x >> y;
        --x, --y;
        g[x].push_back(y);
    }
    cout << cnt_topological_sort(g) << endl;
    return 0;
}