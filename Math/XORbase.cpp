#include <bits/stdc++.h>

/* XOR���Z�ɂ���������Ǘ����� */
template<typename T>
struct XORbase{
private:
    std::vector<T> base;
    T get_MSB(T x){
        return x & (-x);
    }
public:
    XORbase() {}
    /* ����̊���p���đ|���o�� */
    T sweep(T v){
        for (T b : base)
            if (get_MSB(b) & v)
                v ^= b;
        return v;
    }
    /* v��ǉ�����. �ǉ�������true, ����Ȃ����false */
    bool insert(T v){
        T tmp = sweep(v);
        if (tmp == 0) return false;
        base.push_back(tmp);
        return true;
    }
};