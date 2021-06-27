#include <bits/stdc++.h>

struct BipartiteMatching{
private:
    int n, m;
    std::vector<std::vector<int>> graph;
    std::vector<int> dist, match;
    std::vector<bool> used, visited;
    void bfs(void){
        dist.assign(n, -1);
        std::queue<int> q;
        for (int i = 0; i < n; ++i){
            if (!used[i]){
                q.push(i);
                dist[i] = 0;
            }
        }
        while (!q.empty()){
            int a = q.front();
            q.pop();
            for (int b : graph[a]){
                int c = match[b];
                if (c >= 0 && dist[c] == -1){
                    dist[c] = dist[a] + 1;
                    q.push(c);
                }
            }
        }
    }
    bool dfs(int a){
        visited[a] = true;
        for (int b : graph[a]){
            int c = match[b];
            if (c < 0 || (!visited[c] && dist[c] == dist[a] + 1 && dfs(c))){
                match[b] = a;
                used[a] = true;
                return true;
            }
        }
        return false;
    }
public:
    BipartiteMatching(int n, int m) : n(n), m(m) {
        graph.resize(n);
        match.assign(m, -1);
        used.assign(n, false);
    }
    void add_edge(int u, int v){
        graph[u].push_back(v);
    }
    std::pair<int, std::vector<std::pair<int, int>>> bipartite_matching(void){
        int ret1 = 0;
        while (true){
            bfs();
            visited.assign(n, false);
            int flow = 0;
            for (int i = 0; i < n; ++i)
                if (!used[i] && dfs(i))
                    ++flow;
            if (flow == 0) break;
            ret1 += flow;
        }
        std::vector<std::pair<int, int>> ret2;
        for (int i = 0; i < m; ++i)
            if (match[i] != -1)
                ret2.emplace_back(match[i], i);
        std::sort(ret2.begin(), ret2.end());
        return {ret1, ret2};
    }
};