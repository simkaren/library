#include <bits/stdc++.h>

/*
    重さw[i],価値v[i]の品物n個があるとき、
        max_value[j] : 重さj以内で選べる価値の最大値
                            (j = 0,1,2,...,wmax)
    なる配列max_valueを計算して返す.
 */
std::vector<long long> knapsack(std::vector<long long>& w, std::vector<long long>& v, int n, int wmax){
    std::vector<long long> dp(wmax + 1, 0);
    for (int i = 0; i < n; ++i){
        std::vector<long long> new_dp = dp;
        for (int j = 0; j <= wmax; ++j)
            if (j >= w[i])
                new_dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
        dp = new_dp;
    }
    return dp;
}