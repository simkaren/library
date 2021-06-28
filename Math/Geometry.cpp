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
    return std::abs(p1.first - p2.first) < eps && std::abs(p1.second - p2.second) < eps;
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

// |l - r|
template<typename T>
long double distl(const point<T>& l, const point<T>& r){ return absl(l - r); }
template<typename T>
double dist(const point<T>& l, const point<T>& r){ return (double)distl(l, r); }

// rotate p by theta around the origin
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
using points = std::vector<point<T>>;
template<typename T>
using polygon = std::vector<point<T>>;

// closest pair of points
template<typename T>
long double __closest_pair_of_points(points<T>& ps, int l, int r, long double eps = 1e-8L){
    if (r - l <= 1) return std::numeric_limits<long double>::max();
    const int m = (l + r) / 2;
    long double x_mid = ps[m].first;
    long double left_half = __closest_pair_of_points(ps, l, m);
    long double right_half = __closest_pair_of_points(ps, m, r);
    long double res = std::min(left_half, right_half);
    std::inplace_merge(
        ps.begin() + l, ps.begin() + m, ps.begin() + r,
        [](const point<T> a, const point<T> b){
            return a.second < b.second;
        }
    );
    std::vector<int> idx;
    for (int i = l; i < r; ++i){
        if (std::abs(ps[i].first - x_mid) > res + eps)
            continue;
        for (int j = (int)idx.size() - 1; j >= 0; --j){
            long double dy = ps[i].second - ps[idx[j]].second;
            if (dy > res + eps) break;
            res = std::min(res, distl(ps[i], ps[idx[j]]));
        }
        idx.push_back(i);
    }
    return res;
}
template<typename T>
long double closest_pair_of_points(points<T> p, long double eps = 1e-8L){
    std::sort(p.begin(), p.end());
    return __closest_pair_of_points(p, 0, (int)p.size(), eps);
}

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
using segment = std::pair<point<T>, point<T>>;

template<typename T>
struct line{
    point<T> first, second;
    line() {}
    line(point<T> p1, point<T> p2){
        first = p1, second = p2;
    }
};

// l1 // l2?
template<typename T>
bool parallel(const line<T>& l1, const line<T>& l2, long double eps = 1e-8L){
    T crs = cross(l1.second - l1.first, l2.second - l2.first);
    return std::abs(crs) < eps;
}

// l1 ⊥ l2?
template<typename T>
bool orthogonal(const line<T>& l1, const line<T>& l2, long double eps = 1e-8L){
    T d = dot(l1.second - l1.first, l2.second - l2.first);
    return std::abs(d) < eps;
}

// orthogonal projection of p onto l
template<typename T>
point<long double> projectionl(const point<T>& p, const line<T>& l){
    long double tmp = dot(p - l.first, l.second - l.first);
    long double l_len = absl(l.second - l.first);
    tmp /= l_len * l_len;
    long double x = l.first.first + (l.second.first - l.first.first) * tmp;
    long double y = l.first.second + (l.second.second - l.first.second) * tmp;
    return {x, y};
}
template<typename T>
point<double> projection(const point<T>& p, const line<T>& l){
    point<long double> tmp = projectionl(p, l);
    return {(double)tmp.first, (double)tmp.second};
}

// reflection of p onto l
template<typename T>
point<long double> reflectionl(const point<T>& p, const line<T>& l){
    point<long double> pj = projectionl(p, l);
    long double x = 2 * pj.first - p.first;
    long double y = 2 * pj.second - p.second;
    return {x, y};
}
template<typename T>
point<double> reflection(const point<T>& p, const line<T>& l){
    point<long double> tmp = reflectionl(p, l);
    return {(double)tmp.first, (double)tmp.second};
}

// counter clockwise
// 1: p0, p1, p2 make a counterclockwise turn
// 2: p0, p1, p2 make a clockwise turn
// 3: p2 is on p0-p1 line and p2, p0, p1 in this order
// 4: p2 is on p0-p1 line and p0, p1, p2 in this order
// 5: p2 is on a segment p0-p1
template<typename T>
int ccw(const point<T>& p0, const point<T>& p1, const point<T>& p2, long double eps = 1e-8L){
    point<T> v1 = p1 - p0, v2 = p2 - p0;
    if (cross(v1, v2) > eps) return 1;
    if (cross(v1, v2) < -eps) return 2;
    if (dot(v1, v2) < 0) return 3;
    if (absl(v1) < absl(v2)) return 4;
    return 5;
}

// intersect
template<typename T>
bool intersect(const segment<T>& s1, const segment<T>& s2, long double eps = 1e-8L){
    auto f = [](int c) -> int{
        if (c == 1 || c == 3) return 1;
        else if (c == 2 || c == 4) return -1;
        return 0;
    };
    int ccw1 = f(ccw(s1.first, s1.second, s2.first, eps));
    int ccw2 = f(ccw(s1.first, s1.second, s2.second, eps));
    int ccw3 = f(ccw(s2.first, s2.second, s1.first, eps));
    int ccw4 = f(ccw(s2.first, s2.second, s1.second, eps));
    return (ccw1 * ccw2 <= 0 && ccw3 * ccw4 <= 0);
}
template<typename T>
bool intersect(const segment<T>& s, const line<T>& l, long double eps = 1e-8L){
    point<T> ls_f = l.second - l.first;
    return cross(ls_f, s.first - l.first) * cross(ls_f, s.second - l.first) < eps;
}

// cross point
template<typename T>
point<long double> crosspointl(const line<T>& l1, const line<T>& l2, long double eps = 1e-8L){
    long double crs1 = cross(l1.second - l1.first, l2.second - l2.first);
    long double crs2 = cross(l1.second - l1.first, l1.second - l2.first);
    if (std::abs(crs1) < eps && std::abs(crs2) < eps)
        return {(long double)l2.first.first, (long double)l2.first.second};
    long double x = l2.first.first + (l2.second.first - l2.first.first) * crs2 / crs1;
    long double y = l2.first.second + (l2.second.second - l2.first.second) * crs2 / crs1;
    return {x, y};
}
template<typename T>
point<double> crosspoint(const line<T>& l1, const line<T>& l2, long double eps = 1e-8L){
    point<long double> cp = crosspointl(l1, l2, eps);
    return {(double)cp.first, (double)cp.second};
}

// distance
template<typename T>
long double distl(const point<T>& p, const line<T>& l){
    point<long double> prj = projectionl(p, l);
    prj.first -= p.first;
    prj.second -= p.second;
    return absl(prj);
}
template<typename T>
double dist(const point<T>& p, const line<T>& l){
    return (double)distl(p, l);
}
template<typename T>
long double distl(const point<T>& p, const segment<T>& s, long double eps = 1e-8L){
    line<T> l(s.first, s.second);
    point<long double> prj = projectionl(p, l);
    point<long double> s1{(long double)s.first.first, (long double)s.first.second};
    point<long double> s2{(long double)s.second.first, (long double)s.second.second};
    int c = ccw(s1, s2, prj, eps);
    if (c == 5){
        prj.first -= p.first;
        prj.second -= p.second;
        return absl(prj);
    }
    point<long double> p_ld{(long double)p.first, (long double)p.second};
    point<long double> tmp1 = s1 - p_ld;
    point<long double> tmp2 = s2 - p_ld;
    return std::min(absl(tmp1), absl(tmp2));
}
template<typename T>
double dist(const point<T>& p, const segment<T>& s, long double eps = 1e-8L){
    return (double)distl(p, s, eps);
}
template<typename T>
long double distl(const segment<T>& s1, const segment<T>& s2, long double eps = 1e-8L){
    if (intersect(s1, s2, eps)) return 0;
    return std::min({
        distl(s1.first, s2, eps), distl(s1.second, s2, eps),
        distl(s2.first, s1, eps), distl(s2.second, s1, eps)
    });
}
template<typename T>
double dist(const segment<T>& s1, const segment<T>& s2, long double eps = 1e-8L){
    return (double)distl(s1, s2, eps);
}
template<typename T>
long double distl(const segment<T>& s, const line<T>& l, long double eps = 1e-8L){
    if (intersect(s, l, eps)) return 0;
    return std::min(distl(s.first, l), distl(s.second, l));
}
template<typename T>
double dist(const segment<T>& s, const line<T>& l, long double eps = 1e-8L){
    return (double)distl(s, l, eps);
}

} // namespace geometry