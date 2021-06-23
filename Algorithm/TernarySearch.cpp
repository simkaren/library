#include <bits/stdc++.h>

// 下凸関数f(x)の[mn, mx]での最小値を与えるxを求める.
long doubleTernarySearch(long double(*f)(long double), long double mn, long double mx, long double eps = 1e-10){
    while (mx - mn > e){
        long double mid_l = (mx / 3) + ((2 * mn) / 3);
        long double mid_r = ((2 * mx) / 3) + (mn / 3);
        if (f(mid_l) >= f(mid_r))
            mn = mid_l;
        else
            mx = mid_r;        
    }
    return mx;
}