#include <bits/stdc++.h>

/* XOR演算における基底を管理する */
template<typename T>
struct XORbase{
private:
    std::vector<T> base;
    T get_MSB(T x){
        return x & (-x);
    }
public:
    XORbase() {}
    /* 現状の基底を用いて掃き出す */
    T sweep(T v){
        for (T b : base)
            if (get_MSB(b) & v)
                v ^= b;
        return v;
    }
    /* vを追加する. 追加されればtrue, されなければfalse */
    bool insert(T v){
        T tmp = sweep(v);
        if (tmp == 0) return false;
        base.push_back(tmp);
        return true;
    }
};