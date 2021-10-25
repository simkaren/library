#include <bits/stdc++.h>

struct SegmentTreeBeats{
    using ll = long long;
private:
    const ll INF = std::numeric_limits<ll>::max();
    const ll mINF = std::numeric_limits<ll>::min();
    int n, n0;
    std::vector<ll> max_v, smax_v, max_c;
    std::vector<ll> min_v, smin_v, min_c;
    std::vector<ll> sum, len, ladd, lval;

    void update(int k) {
        sum[k] = sum[2 * k + 1] + sum[2 * k + 2];
        if (max_v[2 * k + 1] < max_v[2 * k + 2]) {
            max_v[k] = max_v[2 * k + 2];
            max_c[k] = max_c[2 * k + 2];
            smax_v[k] = std::max(max_v[2 * k + 1], smax_v[2 * k + 2]);
        } 
        else if (max_v[2 * k + 1] > max_v[2 * k + 2]) {
            max_v[k] = max_v[2 * k + 1];
            max_c[k] = max_c[2 * k + 1];
            smax_v[k] = std::max(smax_v[2 * k + 1], max_v[2 * k + 2]);
        }
        else {
            max_v[k] = max_v[2 * k + 1];
            max_c[k] = max_c[2 * k + 1] + max_c[2 * k + 2];
            smax_v[k] = std::max(smax_v[2 * k + 1], smax_v[2 * k + 2]);
        }
        if (min_v[2 * k + 1] < min_v[2 * k + 2]) {
            min_v[k] = min_v[2 * k + 1];
            min_c[k] = min_c[2 * k + 1];
            smin_v[k] = std::min(smin_v[2 * k + 1], min_v[2 * k + 2]);
        }
        else if (min_v[2 * k + 1] > min_v[2 * k + 2]) {
            min_v[k] = min_v[2 * k + 2];
            min_c[k] = min_c[2 * k + 2];
            smin_v[k] = std::min(min_v[2 * k + 1], smin_v[2 * k + 2]);
        }
        else {
            min_v[k] = min_v[2 * k + 1];
            min_c[k] = min_c[2 * k + 1] + min_c[2 * k + 2];
            smin_v[k] = std::min(smin_v[2 * k + 1], smin_v[2 * k + 2]);
        }
    }

    void update_node_max(int k, ll x){
        sum[k] += (x - max_v[k]) * max_c[k];
        if (max_v[k] == min_v[k]){
            max_v[k] = x;
            min_v[k] = x;
        }
        else if (max_v[k] == smin_v[k]){
            max_v[k] = x;
            smin_v[k] = x;
        }
        else max_v[k] = x;
        if (lval[k] != INF && x < lval[k])
            lval[k] = x;
    }

    void update_node_min(int k, ll x){
        sum[k] += (x - min_v[k]) * min_c[k];
        if (max_v[k] == min_v[k]){
            max_v[k] = x;
            min_v[k] = x;
        }
        else if (smax_v[k] == min_v[k]){
            min_v[k] = x;
            smax_v[k] = x;
        }
        else min_v[k] = x;
        if (lval[k] != INF && lval[k] < x)
            lval[k] = x;
    }

    void _update_min(ll x, int a, int b, int k, int l, int r){
        if (b <= l || r <= a || max_v[k] <= x) return;
        if (a <= l && r <= b && smax_v[k] < x){
            update_node_max(k, x);
            return;
        }
        push(k);
        _update_min(x, a, b, 2 * k + 1, l, (l + r) / 2);
        _update_min(x, a, b, 2 * k + 2, (l + r) / 2, r);
        update(k);
    }

    void _update_max(ll x, int a, int b, int k, int l, int r){
        if (b <= l || r <= a || x <= min_v[k]) return;
        if (a <= l && r <= b && x < smin_v[k]){
            update_node_min(k, x);
            return;
        }
        push(k);
        _update_max(x, a, b, 2 * k + 1, l, (l + r) / 2);
        _update_max(x, a, b, 2 * k + 2, (l + r) / 2, r);
        update(k);
    }

    void addall(int k, ll x){
        max_v[k] += x;
        if (smax_v[k] != mINF) smax_v[k] += x;
        min_v[k] += x;
        if (smin_v[k] != INF) smin_v[k] += x;
        sum[k] += len[k] * x;
        if (lval[k] != INF) lval[k] += x;
        else ladd[k] += x;
    }

    void updateall(int k, ll x){
        max_v[k] = x;
        smax_v[k] = mINF;
        min_v[k] = x;
        smin_v[k] = INF;
        max_c[k] = len[k];
        min_c[k] = len[k];
        sum[k] = x * len[k];
        lval[k] = x;
        ladd[k] = 0;
    }

    void _add_val(ll x, int a, int b, int k, int l, int r){
        if (b <= l || r <= a) return;
        if (a <= l && r <= b){
            addall(k, x);
            return;
        }
        push(k);
        _add_val(x, a, b, 2 * k + 1, l, (l + r) / 2);
        _add_val(x, a, b, 2 * k + 2, (l + r) / 2, r);
        update(k);
    }

    void _update_val(ll x, int a, int b, int k, int l, int r){
        if (b <= l || r <= a) return;
        if (a <= l && r <= b){
            updateall(k, x);
            return;
        }
        push(k);
        _update_val(x, a, b, 2 * k + 1, l, (l + r) / 2);
        _update_val(x, a, b, 2 * k + 2, (l + r) / 2, r);
        update(k);
    }

    ll _query_max(int a, int b, int k, int l, int r){
        if (b <= l || r <= a) return mINF;
        if (a <= l && r <= b) return max_v[k];
        push(k);
        ll lv = _query_max(a, b, 2 * k + 1, l, (l + r) / 2);
        ll rv = _query_max(a, b, 2 * k + 2, (l + r) / 2, r);
        return std::max(lv, rv);
    }

    ll _query_min(int a, int b, int k, int l, int r){
        if (b <= l || r <= a) return INF;
        if (a <= l && r <= b) return min_v[k];
        push(k);
        ll lv = _query_min(a, b, 2 * k + 1, l, (l + r) / 2);
        ll rv = _query_min(a, b, 2 * k + 2, (l + r) / 2, r);
        return std::min(lv, rv);
    }

    ll _query_sum(int a, int b, int k, int l, int r){
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return sum[k];
        push(k);
        ll lv = _query_sum(a, b, 2 * k + 1, l, (l + r) / 2);
        ll rv = _query_sum(a, b, 2 * k + 2, (l + r) / 2, r);
        return lv + rv;
    }

    void push(int k){
        if (n0 - 1 <= k) return;
        if (lval[k] != INF){
            updateall(2 * k + 1, lval[k]);
            updateall(2 * k + 2, lval[k]);
            lval[k] = INF;
            return;
        }
        if (ladd[k] != 0){
            addall(2 * k + 1, ladd[k]);
            addall(2 * k + 2, ladd[k]);
            ladd[k] = 0;
        }
        if (max_v[k] < max_v[2 * k + 1])
            update_node_max(2 * k + 1, max_v[k]);
        if (min_v[2 * k + 1] < min_v[k])
            update_node_min(2 * k + 1, min_v[k]);
        if(max_v[k] < max_v[2 * k + 2]) 
            update_node_max(2 * k + 2, max_v[k]);
        if(min_v[2 * k + 2] < min_v[k]) 
            update_node_min(2 * k + 2, min_v[k]);
    }

    void prepare(int sz){
        n = sz;
        n0 = 1;
        while (n0 < n)
            n0 <<= 1;
        max_v.resize(2 * n0, 0);
        smax_v.resize(2 * n0, 0);
        max_c.resize(2 * n0, 0);
        min_v.resize(2 * n0, 0);
        smin_v.resize(2 * n0, 0);
        min_c.resize(2 * n0, 0);
        sum.resize(2 * n0, 0);
        len.resize(2 * n0, 0);
        ladd.resize(2 * n0, 0);
        lval.resize(2 * n0, INF);
        len[0] = n0;
        for (int i = 0; i < n0 - 1; ++i)
            len[2 * i + 1] = len[2 * i + 2] = len[i] / 2;
        for (int i = 0; i < n; ++i){
            smax_v[n0 - 1 + i] = mINF;
            smin_v[n0 - 1 + i] = INF;
            max_c[n0 - 1 + i] = 1;
            min_c[n0 - 1 + i] = 1;
        }
        for (int i = n; i < n0; ++i){
            max_v[n0 - 1 + i] = mINF;
            smax_v[n0 - 1 + i] = mINF;
            min_v[n0 - 1 + i] = INF;
            smin_v[n0 - 1 + i] = INF;
        }
    }
public:
    SegmentTreeBeats() {}

    SegmentTreeBeats(int sz){
       prepare(sz);
       for (int i = n0 - 2; i >= 0; --i)
            update(i);
    }

    SegmentTreeBeats(const std::vector<ll>& v){
        prepare(int(v.size()));
        for (int i = 0; i < int(v.size()); ++i){
            max_v[n0 - 1 + i] = v[i];
            min_v[n0 - 1 + i] = v[i];
            sum[n0 - 1 + i] = v[i];
        }
        for (int i = n0 - 2; i >= 0; --i)
            update(i);
    }

    // for i in [l, r), update v[i] to min(v[i], x)
    void range_chmin(int l, int r, ll x){
        _update_min(x, l, r, 0, 0, n0);
    }

    // for i in [l, r), update v[i] to max(v[i], x)
    void range_chmax(int l, int r, ll x){
        _update_max(x, l, r, 0, 0, n0);
    }

    // for i in [l, r), add x to v[i]
    void range_add(int l, int r, ll x){
        _add_val(x, l, r, 0, 0, n0);
    }

    // for i in [l, r), update v[i] to x
    void range_update(int l, int r, ll x){
        _update_val(x, l, r, 0, 0, n0);
    }

    // calculate min v[i] for i in [l, r)
    ll get_min(int l, int r){
        return _query_min(l, r, 0, 0, n0);
    }

    // calculate max v[i] for i in [l, r)
    ll get_max(int l, int r){
        return _query_max(l, r, 0, 0, n0);
    }

    // calculate sum v[i] for i in [l, r)
    ll get_sum(int l, int r){
        return _query_sum(l, r, 0, 0, n0);
    }

    // print v
    void print(void){
        for (int i = 0; i < n; ++i)
            std::cout << get_sum(i, i + 1) << ' ';
        std::cout << std::endl;
    }
};