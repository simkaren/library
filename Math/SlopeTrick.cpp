#include <bits/stdc++.h>

struct SlopeTrick{
    using ll = long long;
private:
    const ll INF = (1LL << 60);
    ll m;
    std::priority_queue<ll> L;
    std::priority_queue<ll, std::vector<ll>, std::greater<ll>> R;
    ll add_L, add_R;
public:
    /* コンストラクタ */
    SlopeTrick(void) : m(0LL), add_L(0LL), add_R(0LL) {
        L.push(-INF);
        R.push(INF);
    }
    /* 関数の最小値を取得 */
    ll get_min(void){ return m; }
    /* 関数の最小値を与えるxの範囲を取得 */
    std::pair<ll, ll> get_min_range(void){
        const ll l = L.top() + add_L;
        const ll r = R.top() + add_R;
        return {l, r};
    }
    /* 関数に定数vを加算 */
    void add_constant(ll v){
        m += v;
    }
    /* 関数に関数max(x-a,0)を加算 */
    void add_func1(ll a){
        const ll l = L.top() + add_L;
        m += std::max(0LL, l - a);
        L.push(a - add_L);
        R.push(L.top() + add_L - add_R);
        L.pop();
    }
    /* 関数に関数max(a-x,0)を加算 */
    void add_func2(ll a){
        const ll r = R.top() + add_R;
        m += std::max(a - r, 0LL);
        R.push(a - add_R);
        L.push(R.top() + add_R - add_L);
        R.pop();
    }
    /* 関数に関数abs(x-a)を加算 */
    void add_func3(ll a){
        add_func1(a);
        add_func2(a);
    }
    /* 関数を関数の累積最小値に書き換える */
    void acc_min_L(void){
        R = std::priority_queue<ll, std::vector<ll>, std::greater<ll>>();
        add_R = 0;
        R.push(INF);
    }
    /* 関数を関数の右側から見た累積最小値に書き換える */
    void acc_min_R(void){
        L = std::priority_queue<ll>();
        add_L = 0;
        L.push(-INF);
    }
    /* 関数をaだけ平行移動する */
    void shift(ll a){
        add_L += a;
        add_R += a;
    }
    /* 関数fをmin_{x-b<=y<=x-a}f(y)に書き換える */
    void sliding_window_min(ll a, ll b){
        assert(a <= b);
        add_L += a;
        add_R += b;
    }
};

/* https://atcoder.jp/contests/abc127/submissions/21162823 */
int main(void){
    SlopeTrick f;
    int Q; std::cin >> Q;
    while (Q--){
        int t; std::cin >> t;
        if (t == 1){
            long long a, b;
            std::cin >> a >> b;
            f.add_func3(a);
            f.add_constant(b);
        }
        else{
            long long mn = f.get_min();
            const auto [l, r] = f.get_min_range();
            std::cout << l << " " << mn << std::endl;
        }
    }
    return 0;
}