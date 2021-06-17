#include <bits/stdc++.h>

namespace geometry{

template<typename T>
struct point : public std::pair<T, T> {
public:
    point<T>(void) {}
    point<T>(T x, T y){
        this->first = x;
        this->second = y;
    }
    point<T>(std::pair<T, T> p){
        this->first = p.first;
        this->second = p.second;
    }
    point<T>& operator+=(const point<T>& obj){
        this->first += obj.first;
        this->second += obj.second;
        return *this;
    }
    point<T>& operator-=(const point<T>& obj){
        this->first -= obj.first;
        this->second -= obj.second;
        return *this;
    }
    point<T>& operator*=(const T& val){
        this->first *= val;
        this->second *= val;
        return *this;
    }
    point<T>& operator/=(const T& val){
        this->first /= val;
        this->second /= val;
        return *this;
    }
    point<T> operator+(void){ return *this; }
    point<T> operator-(void){
        return {
            -(this->first), -(this->second)
        };
    }
    friend point<T> operator+(const point<T>& l, const point<T>& r){
        return (point<T>(l) += r);
    }
    friend point<T> operator-(const point<T>& l, const point<T>& r){
        return (point<T>(l) -= r);
    }
    friend point<T> operator*(const point<T>& l, const T& val){
        return (point<T>(l) *= val);
    }
    friend point<T> operator*(const T& val, const point<T>& r){
        return (point<T>(r) *= val);
    }
    friend point<T> operator/(const point<T>& l, const T& val){
        return (point<T>(l) /= val);
    }
    friend constexpr std::istream& operator>>(std::istream& is, point<T>& p) noexcept{
        is >> p.first >> p.second;
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, point<T>& p) noexcept{
        os << p.first << " " << p.second;
        return os;
    }
};

// p1 == p2?
template<typename T>
bool equal(const point<T>& p1, const point<T>& p2, long double eps = 1e-8L){
    return absl(p1.first - p2.first) < eps && absl(p1.second - p2.second) < eps;
}

// cross product
template<typename T>
T cross(const point<T>& l, const point<T>& r){
    return l.first * r.second - l.second * r.first;
}

// inner product
template<typename T>
T dot(const point<T>& l, const point<T>& r){
    return l.first * r.first + l.second * r.second;
}

// |p|
template<typename T>
long double absl(const point<T>& p){
    long double tmp = p.first * (long double)p.first;
    tmp += p.second * (long double)p.second;
    return std::sqrt(tmp);
}
template<typename T>
double abs(const point<T>& p){ return (double)absl(p); }
template<typename T>
float absf(const point<T>& p){ return (float)absl(p); }

// |l - r|
template<typename T>
long double distl(const point<T>& l, const point<T>& r){ return absl(l - r); }
template<typename T>
double dist(const point<T>& l, const point<T>& r){ return (double)distl(l, r); }
template<typename T>
float distf(const point<T>& l, const point<T>& r){ return (float)distl(l, r); }

// rotate p by theta around the origin
point<float> rotate(const point<float>& p, float theta){
    return point<float>{
        cosf(theta) * p.first - sinf(theta) * p.second,
        sinf(theta) * p.first - cosf(theta) * p.second
    };
}
point<double> rotate(const point<double>& p, double theta){
    return point<double>{
        cos(theta) * p.first - sinf(theta) * p.second,
        sin(theta) * p.first - cos(theta) * p.second
    };
}
point<long double> rotate(const point<long double>& p, long double theta){
    return point<long double>{
        cosl(theta) * p.first - sinl(theta) * p.second,
        sinl(theta) * p.first - cosl(theta) * p.second
    };
}

// calculate the angle of p1-p2-p3
template<typename T>
long double anglel(const point<T>& p1, const point<T>& p2, const point<T>& p3){
    const point<T> v = p2 - p1, w = p3 - p2;
    long double alpha = atan2l(v.second, v.first);
    long double beta = atan2l(w.second, w.first);
    if (alpha > beta) std::swap(alpha, beta);
    long double theta = beta - alpha;
    const long double pi = acosl(-1);
    if (theta < pi) return theta;
    return 2 * pi - theta;
}
template<typename T>
double angle(const point<T>& p1, const point<T>& p2, const point<T>& p3){
    return (double)anglel(p1, p2, p3);
}
template<typename T>
float anglef(const point<T>& p1, const point<T>& p2, const point<T>& p3){
    return (float)anglel(p1, p2, p3);
}

template<typename T>
using points = std::vector<point<T>>;
template<typename T>
using polygon = std::vector<point<T>>;

// convex hull
template<typename T>
polygon<T> convex_hull(points<T> p, long double eps = 1e-8L){
    int n = (int)p.size(), k = 0;
    if (n <= 2) return p;
    std::sort(p.begin(), p.end());
    points<T> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++])
        while (k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < eps)
            --k;
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--])
        while (k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < eps)
            --k;
    ch.resize(k - 1);
    return ch;
}

// p in poly? (in : 2, on : 1, out : 0)
template<typename T>
int contain(const point<T>& p, const polygon<T>& poly, long double eps = 1e-8L){
    bool in = false;
    const int n = (int)poly.size();
    for (int i = 0; i < n; ++i){
        point<T> a = poly[i] - p, b = poly[(i + 1) % n] - p;
        if (a.second > b.second) std::swap(a, b);
        const T crs_ab = cross(a, b);
        if (a.second < eps && eps < b.second && crs_ab < -eps) in = !in;
        if ((crs_ab < 0 ? -crs_ab : crs_ab) < eps && dot(a, b) < eps) return 1;
    }
    return in ? 2 : 0;
}

// area
template<typename T>
long double areal(const polygon<T>& p){
    long double s = 0;
    const int n = (int)p.size();
    for (int i = 0; i < n; ++i)
        s += cross(p[i], p[(i + 1) % n]);
    return s * 0.5L;
}
template<typename T>
double area(const polygon<T>& p){ return (double)areal(p); }
template<typename T>
float areaf(const polygon<T>& p){ return (float)areaf(p); }

} // namespace geometry
