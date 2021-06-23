#include <bits/stdc++.h>

long long cnt_topological_sort(std::vector<std::vector<int>>& g){
    const int n = g.size();
    std::vector<int> bit_flg(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j : g[i])
            bit_flg[i] |= (1 << j);
    std::vector<long long> dp(1 << n, 0);
    dp[0] = 1;
    for (int i = 0; i < (1 << n); ++i)
        for (int j = 0; j < n; ++j)
            if ((i & (1 << j)) == 0 && (i & bit_flg[j]) == 0)
                dp[i | (1 << j)] += dp[i];
    return dp[(1 << n) - 1];
}