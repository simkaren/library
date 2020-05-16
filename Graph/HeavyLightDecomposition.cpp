#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct HLD {
	vector<vector<pair<int, T>>> g;
	int n;
	vector<int> subsz, depth, parent;
	vector<vector<T>> chain_edge;
	vector<vector<int>> chain_node;
	map<int, int> chain_top, chain_id, id_in_chain;

	/* constructor */
	HLD(vector<vector<pair<int, T>>>& g) {
		this->g = g; n = g.size();
		parent.resize(g.size());
		subsz.resize(g.size());
		depth.resize(g.size());
	}

	/* init parent, depth, and subsz */
	int dfs_sz(int s = 0, int p = -1, int dep = 0) {
		parent[s] = p;
		depth[s] = dep;
		int sz = 1;
		if (g[s].size() > 2 && g[s][0].first == p)
			swap(g[s][0], g[s][1]); // g[s][0] must be heavy
		for (int i = 0; i < g[s].size(); ++i) {
			if (g[s][i].first != p) {
				sz += dfs_sz(g[s][i].first, s, dep + 1);
				if (subsz[g[s][0].first] < subsz[g[s][i].first])
					swap(g[s][0], g[s][i]); // g[s][0] must be heavy
			}
		}
		subsz[s] = sz;
		return sz;
	}

	/* HL Decomposition */
	void dfs_hld(int s, int& cid) {
		chain_id[s] = cid;
		for (int i = 0; i < g[s].size(); ++i) {
			if (g[s][i].first != parent[s]) {
				if (i == 0) {
					chain_edge.resize(cid + 1);
					chain_node.resize(cid + 1);
					chain_edge[cid].push_back(g[s][i].second);
					chain_node[cid].push_back(g[s][i].first);
					id_in_chain[g[s][i].first] = chain_edge[cid].size();
					dfs_hld(g[s][i].first, cid);
				}
				else {
					++cid;
					chain_edge.resize(cid + 1);
					chain_node.resize(cid + 1);
					chain_edge[cid].push_back(g[s][i].second);
					chain_node[cid].push_back(g[s][i].first);
					id_in_chain[g[s][i].first] = chain_edge[cid].size();
					dfs_hld(g[s][i].first, cid);
				}
			}
		}
	}

	/* the number of chain */
	int chain_number() {
		return chain_node.size();
	}

	/* find chain_top */
	void find_chain_top() {
		for (int i = 0; i < chain_number(); ++i)
			chain_top[i] = parent[chain_node[i][0]];
	}

	/* build */
	void build() {
		dfs_sz();
		int cid = 0;
		dfs_hld(0, cid);
		find_chain_top();
		/* 【TODO】*/
		// Prepare Segtrees or someting
	}

	/* find lca */
	int LCA(int s, int t) {
		if (chain_id[s] < chain_id[t]) swap(s, t);
		while (chain_id[s] != chain_id[t]) {
			s = chain_top[chain_id[s]];
			if (chain_id[s] < chain_id[t]) swap(s, t);
		}
		if (depth[s] < depth[t]) return s;
		return t;
	}

	/* sub query */
	// 【TODO】
	T query_in_chain(int cid, int s, int t) {
		// s <= t, [s, t]
	}
	T query_in_chain_reverse(int cid, int s, int t) {
		// t <= s, [t, s]
		// return query_in_chain(cid, t, s);
	}
	void chain_update(int cid, int id, T d) {
	}
	T merge(T l, T r) {
	}

	/* edge query */
	T edge_query(int s, int t, T ei) {
		int lca = LCA(s, t);
		// s to lca
		T left = ei;
		while (s != lca) {
			if (chain_id[s] != chain_id[lca]) {
				T tmp = query_in_chain_reverse(
					chain_id[s], id_in_chain[s] - 1, 0
				);
				left = merge(left, tmp);
				s = chain_top[chain_id[s]];
			}
			else {
				T tmp = query_in_chain_reverse(
					chain_id[s], id_in_chain[s] - 1, id_in_chain[lca]
				);
				left = merge(left, tmp);
				s = lca;
			}
		}
		// lca to t
		T right = ei;
		while (t != lca) {
			if (chain_id[t] != chain_id[lca]) {
				T tmp = query_in_chain(
					chain_id[t], 0, id_in_chain[t] - 1
				);
				right = merge(tmp, right);
				t = chain_top[chain_id[t]];
			}
			else {
				T tmp = query_in_chain(
					chain_id[t], id_in_chain[lca], id_in_chain[t] - 1
				);
				right = merge(tmp, right);
				t = lca;
			}
		}
		return merge(left, right);
	}

	/* edge update query */
	void update(int s, int t, T d) {
		if (depth[s] >= depth[t]) swap(s, t);
		if (chain_id[s] == chain_id[t])
			chain_update(chain_id[s], id_in_chain[s], d);
		else
			chain_update(chain_id[t], 0, d);
	}
};