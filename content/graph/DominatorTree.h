/**
 * Author: Hanfei Chen
 * Date: 2022-10-29 
 * Source: https://judge.yosupo.jp/submission/184
 * Description: Generates the dominator tree for a given directed graph
 * Usage: auto idom = dominator_tree(adj, root).idom;
 */
#pragma once

// idom[i]: intermediate dominator of i
// -1 if i is the root or not reachable from root
struct dominator_tree {
	/// start-hash
	int n;
	vector<vi> adj, radj, bucket;
	vi idom, sdom, us, id, rid, par, mi, anc;
	dominator_tree(vector<vi> adj_, int root) : n(int(adj_.size())),
	adj(adj_), radj(n), bucket(n),
	idom(n, -1), sdom(n), us(n), id(n, -1), rid(n, -1),
	par(n, -1), mi(n), anc(n, -1) {
		rep(i,0,n) for (int j : adj[i]) radj[j].push_back(i);
		iota(all(sdom), 0);
		iota(all(mi), 0);
		int sz = 0;
		dfs(root, -1, sz);
		per(i,1,sz) {
			int w = rid[i];
			for (int v : radj[w]) {
				if (id[v] == -1) continue;
				getanc(v);
				if (id[sdom[mi[v]]] < id[sdom[w]]) {
					sdom[w] = sdom[mi[v]];
				}
			}
			bucket[sdom[w]].push_back(w);
			for (int v : bucket[par[w]]) {
				getanc(v);
				us[v] = mi[v];
			}
			bucket[par[w]].clear();
			anc[w] = par[w];
		}
		rep(i,1,sz) {
			int w = rid[i];
			if (sdom[w] == sdom[us[w]]) idom[w] = sdom[w];
			else idom[w] = idom[us[w]];
		}
	} /// end-hash
	/// start-hash
	int getanc(int v) {
		if (anc[v] == -1) return v;
		int a = getanc(anc[v]);
		if (id[sdom[mi[anc[v]]]] < id[sdom[mi[v]]]) {
			mi[v] = mi[anc[v]];
		}
		return anc[v] = a;
	}
	void dfs(int v, int p, int& i) {
		if (id[v] != -1) return;
		id[v] = i;
		rid[i++] = v;
		par[v] = p;
		for (int w : adj[v]) dfs(w, v, i);
	} /// end-hash
};
