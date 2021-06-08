#include <bits/stdc++.h>

struct UnionFind{
private:
    std::vector<int> data;
public:
    /* constructor */
    UnionFind(int sz){ data.assign(sz,-1); }
    /* merge the set to which x belongs and the set to which y belongs */
    bool unite(int x,int y){
        x = find(x); y = find(y);
        if (x == y) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }
    /* find the root of k */
    int find(int k){
        if (data[k] < 0) return k;
        return data[k] = find(data[k]);
    }
    /* return whether x and y belong to the same set */
    bool same(int x, int y){ return find(x) == find(y); }
    /* calculate the size of the set to which k belongs */
    int size(int k){ return -data[find(k)]; }
};