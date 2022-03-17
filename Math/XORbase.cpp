#include <bits/stdc++.h>

/* XOR‰‰Z‚É‚¨‚¯‚éŠî’ê‚ğŠÇ—‚·‚é */
template<typename T>
struct XORbase{
private:
    std::vector<T> base;
    T get_MSB(T x){
        return x & (-x);
    }
public:
    XORbase() {}
    /* Œ»ó‚ÌŠî’ê‚ğ—p‚¢‚Ä‘|‚«o‚· */
    T sweep(T v){
        for (T b : base)
            if (get_MSB(b) & v)
                v ^= b;
        return v;
    }
    /* v‚ğ’Ç‰Á‚·‚é. ’Ç‰Á‚³‚ê‚ê‚Îtrue, ‚³‚ê‚È‚¯‚ê‚Îfalse */
    bool insert(T v){
        T tmp = sweep(v);
        if (tmp == 0) return false;
        base.push_back(tmp);
        return true;
    }
};