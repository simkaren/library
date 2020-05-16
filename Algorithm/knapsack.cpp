#include <bits/stdc++.h>

using namespace std;

#define ll long long

/*
    重さw[i],価値v[i]の品物n個があるとき、
        max_value[j] : 重さj以内で選べる価値の最大値
                            (j = 0,1,2,...,wmax)
    なる配列max_valueを計算して返す.
 */
ll* knapsack(ll* w,ll* v,int n,ll wmax){
    ll** dp = new ll*[n + 1];
    for (int i = 0;i <= n;++i){
        dp[i] = new ll[wmax + 1];
    }
    for (int i = 0;i <= n;++i)
        for (int j = 0;j <= wmax;++j)
            dp[i][j] = 0;
    // fill the dp table
    for (int i = 1;i <= n;++i){
        ll wi = w[i - 1];
        ll vi = v[i - 1];
        for (int j = 0;j <= wmax;++j){
            if (j >= wi){
                dp[i][j] = max({
                    dp[i - 1][j],
                    dp[i - 1][j - wi] + vi
                });
            }
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    for (int i = 0;i < n;++i)
        delete[] dp[i];
    return dp[n];
}