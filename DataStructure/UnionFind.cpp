#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct UnionFind{
    vector<int> data;
    /* constructor */
    UnionFind(int sz){ data.assign(sz,-1); }
    /* merge the set to which x belongs and the set to which y belongs */
    bool unite(int x,int y){
        x = find(x); y = find(y);
        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }
    /* find the root of k */
    int find(int k){
        if (data[k] < 0) return k;
        return data[k] = find(data[k]);
    }
    /* calculate the size of the set to which k belongs */
    int size(int k){ return -data[find(k)]; }
};