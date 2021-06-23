#include <bits/stdc++.h>

/*
    グラフGの頂点sからすべての頂点への最短距離をDijkstra法により求める.
*/
template<typename T>
std::vector<T> dijkstra(int s, std::vector<std::vector<std::pair<int, T>>> &G){
    const int n = G.size();
    std::vector<T> d(n, std::numeric_limits<T>::max());
    std::vector<int> b(n, -1);
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> q;
    d[s] = 0;
    q.emplace(d[s], s);
    while (!q.empty()){
        std::pair<T, int> p = q.top();
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
