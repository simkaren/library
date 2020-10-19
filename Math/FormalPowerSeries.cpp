#include <bits/stdc++.h>

#define ll long long

// 形式的冪級数
template<ll mod = 998244353LL, int size_lim = 10000000>
struct FormalPowerSeries{
private:
    std::vector<ll> a;

    inline ll modpow(ll a, ll b){
        if (b == 0) return 1LL;
        ll tmp = modpow(a, b / 2);
        tmp = tmp * tmp % mod;
        if (b & 1) return tmp * a % mod;
        return tmp;
    }

    static constexpr bool isPrime(ll p){
        if (p == 1LL) return false;
        for (ll i = 2; i * i <= p; ++i)
            if (p % i == 0) return false;
        return true;
    }

    void ntt(std::vector<ll>& a, ll root, bool rev = false){
        const int sz = a.size();
        if (sz == 1) return;
        std::vector<ll> b(sz);
        int r = rev ? (mod - 1 - (mod - 1) / sz) : (mod - 1) / sz;
        ll s = modpow(root, r);
        std::vector<ll> kp(sz / 2 + 1, 1);
        for(int i = 0; i < sz / 2; ++i) kp[i + 1] = kp[i] * s % mod;
        for(int i = 1, l = sz / 2; i < sz; i <<= 1, l >>= 1){
            for(int j = 0, r = 0; j < l; ++j, r += i){
                for(int k = 0, s = kp[i * j]; k < i; ++k){
                    ll p = a[k + r], q = a[k + r + sz / 2];
                    b[k + 2 * r] = (p + q) % mod;
                    b[k + 2 * r + i] = ((p - q) % mod + mod) % mod * s % mod;
                }
            }
            swap(a, b);
        }
        if(rev){
            s = modpow(sz, mod - 2);
            for(int i = 0; i < sz; i++){ a[i] = a[i] * s % mod; }
        }
    }

    std::vector<ll> convolute(std::vector<ll> a, std::vector<ll> b, ll root){
        const int sz = (int)a.size() + (int)b.size() - 1;
        int t = 1;
        while (t < sz) t *= 2;
        a.resize(t, 0); b.resize(t, 0);
        ntt(a, root); ntt(b, root);
        for (int i = 0; i < t; ++i)
            a[i] = a[i] * b[i] % mod;
        ntt(a, root, true);
        a.resize(sz);
        return a;
    }

public:
    // constructor
    FormalPowerSeries(int sz){
        a.resize(std::min(sz, size_lim), 0LL);
    }
    FormalPowerSeries(const std::vector<ll>& init_data){
        int sz = std::min((int)init_data.size(), size_lim);
        a.resize(sz);
        for (int i = 0; i < sz; ++i){
            a[i] = init_data[i] % mod;
            if (a[i] < 0) a[i] += mod;
        }
    }

    // get element
    ll get(int idx){
        assert(idx < size_lim);
        if ((int)a.size() <= idx) return 0LL;
        return a[idx];
    }

    // resize
    void resize(int sz){
        a.resize(std::min(sz, size_lim), 0LL);
    }

    // get prefix ([0, n)])
    FormalPowerSeries<mod, size_lim> prefix(int n){
        const int sz = std::min(n, (int)a.size());
        std::vector<ll> elem(sz, 0LL);
        for (int i = 0; i < sz; ++i)
            elem[i] = a[i];
        return FormalPowerSeries<mod, size_lim>(elem);
    }

    // print elements to stdout
    void print(void){
        int sz = std::min((int)a.size(), size_lim);
        for (int i = 0; i < sz; ++i)
            std::cout << a[i] << (i == sz - 1 ? "\n" : " ");
    }
    void print(int len){
        assert(len <= size_lim);
        const int lst = std::min(len, (int)a.size());
        for (int i = 0; i < lst; ++i)
            std::cout << a[i] << (i == len - 1 ? "\n" : " ");
        for (int i = lst; i < len; ++i)
            std::cout << 0LL << (i == len - 1 ? "\n" : " ");
    }

    // operators
    FormalPowerSeries<mod, size_lim> operator*(const FormalPowerSeries<mod, size_lim>& f){
        static_assert(
            mod == 998244353LL ||
            mod == 163577857LL ||
            mod == 167772161LL ||
            mod == 469762049LL
        );
        constexpr ll r = mod == 998244353LL ? 3LL :
                mod == 163577857LL ? 23LL :
                mod == 167772161LL ? 3LL : 
                3LL; // mod == 469762049LL
        return FormalPowerSeries<mod, size_lim>(convolute(a, f.a, r));
    }
    FormalPowerSeries<mod, size_lim> operator*(const ll& v){
        const ll _v = v % mod;
        const int sz = std::min(size_lim, (int)a.size());
        std::vector<ll> elem(sz);
        for (int i = 0; i < sz; ++i)
            elem[i] = a[i] * _v % mod;
        return FormalPowerSeries<mod, size_lim>(elem);
    }
    FormalPowerSeries<mod, size_lim> operator+(const FormalPowerSeries<mod, size_lim>& f){
        const int tmp = std::max((int)a.size(), (int)(f.a.size()));
        const int sz = std::min(size_lim, tmp);
        std::vector<ll> elem(sz, 0LL);
        for (int i = 0; i < sz; ++i){
            if (i < (int)a.size()) elem[i] += a[i];
            if (i < (int)(f.a.size())) elem[i] += f.a[i];
            if (elem[i] >= mod) elem[i] -= mod;
        }
        return FormalPowerSeries<mod, size_lim>(elem);
    }
    FormalPowerSeries<mod, size_lim> operator-(const FormalPowerSeries<mod, size_lim>& f){
        const int tmp = std::max((int)a.size(), (int)(f.a.size()));
        const int sz = std::min(size_lim, tmp);
        std::vector<ll> elem(sz, 0LL);
        for (int i = 0; i < sz; ++i){
            if (i < (int)a.size()) elem[i] += a[i];
            if (i < (int)(f.a.size())) elem[i] -= f.a[i];
            if (elem[i] < 0) elem[i] += mod;
        }
        return FormalPowerSeries<mod, size_lim>(elem);
    }

    // calculate 1 / self (verified : https://judge.yosupo.jp/submission/27328)
    FormalPowerSeries<mod, size_lim> inverse(void){
        static_assert(isPrime(mod));
        assert(a[0] != 0LL);
        FormalPowerSeries<mod, size_lim> ret((std::vector<ll>){modpow(a[0], mod - 2)});
        for (int i = 1; i < size_lim; i <<= 1)
            ret = (ret + ret - ret * ret * prefix(i << 1)).prefix(i << 1);
        return ret.prefix(size_lim);
    }
};

using fps = FormalPowerSeries<998244353LL, 500000>;

int main(void){
    int N; std::cin >> N;
    std::vector<ll> a(N);
    for (ll& ai : a)
        std::cin >> ai;
    fps f(a);
    fps inv_f = f.inverse();
    for (int i = 0; i < N; ++i)
        std::cout << inv_f.get(i) << " ";
    std::cout << std::endl; 
    return 0;
}