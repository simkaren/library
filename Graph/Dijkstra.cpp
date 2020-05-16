#include <bits/stdc++.h>

usnig namespace std;

#define ll long long

/*
    グラフGの頂点sからすべての頂点への最短距離をDijkstra法により求める.
*/
template<typename T>
vector<T> dijkstra(int s, vector<vector<pair<int, T>>> &G){
    const int n = G.size();
    vector<T> d(n, numeric_limits<T>::max());
    vector<int> b(n, -1);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    d[s] = 0;
    q.emplace(d[s], s);
    while (!q.empty()){
        pair<T, int> p = q.top();
        q.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (auto& e : G[v]){
            int u = e.first;
            T c = e.second;
            if (d[u] > d[v] + c){
                d[u] = d[v] + c;
                b[u] = v;
                q.emplace(d[u], u);
            }
        }
    }
    return d;
}
