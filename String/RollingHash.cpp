#include <bits/stdc++.h>

template<int n_mod = 2>
struct RollingHash{
    using hash_arr = std::array<long long, n_mod>;
    const int base = 1009;
    const long long p_mod[4] = 
    {1000000009LL, 1000000007LL, 998244353LL, 469762049LL};

    std::string text;
    int len;
    std::vector<hash_arr> pw, hs;

    // constructor
    RollingHash(string& S){
        static_assert(1 <= n_mod && n_mod <= 4);
        text = S; len = S.length();
        pw.resize(len + 1);
        hs.resize(len + 1);
        for (int j = 0; j < n_mod; ++j)
            hs[0].at(j) = 0LL, pw[0].at(j) = 1LL;
        for (int i = 0; i < len; ++i){
            for (int j = 0; j < n_mod; ++j){
                hs[i + 1].at(j) = (hs[i].at(j) + text[i]) * base % p_mod[j];
                pw[i + 1].at(j) = pw[i].at(j) * base % p_mod[j];
            }
        }
    } 

    // text[l, r)のハッシュ値を計算する
    hash_arr get_hash(int l, int r){
        hash_arr ret;
        for (int j = 0; j < n_mod; ++j){
            ret.at(j) = hs[r].at(j) - hs[l].at(j) * pw[r - l].at(j) % p_mod[j];
            if (ret.at(j) < 0) ret.at(j) += p_mod[j];
        }
        return ret;
    }

    // text全体のハッシュ値を計算する
    hash_arr get(void){ return hs[len]; }
};