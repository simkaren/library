// 検証済み(https://atcoder.jp/contests/arc054/submissions/7574654)

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

// 下凸関数f(x)の[mn, mx]での最小値を与えるxを求める.
ld TernarySearch(ld(*f)(ld), ld mn, ld mx){
    ld e = 1e-10; // 許容誤差
    while (mx - mn > e){
        ld mid_l = (mx / 3) + ((2 * mn) / 3);
        ld mid_r = ((2 * mx) / 3) + (mn / 3);
        if (f(mid_l) >= f(mid_r))
            mn = mid_l;
        else
            mx = mid_r;        
    }
    return mx;
}

ld p;

ld t(ld x){
    return x + p / pow(2, x / 1.5);
}

signed main(){
    cin >> p;
    ld time = TernarySearch(t, 0.0, 100.0);
    cout << setprecision(20) << t(time) << endl;
    return 0;
}