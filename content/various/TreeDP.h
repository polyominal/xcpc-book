/**
 * Author: Hanfei Chen
 * Date: 2022-12-24
 * Description: Solve for all roots.
 * Usage: auto td = TreeDP<D, int>(adj);
 * Status: tested
 */
#pragma once

template <class D, class E>
struct treedp {
	// modify as needed
	const VV<E>& adj;
	int n;
	V<D> up, pref, dp, dp2, res;
	V<E> par;
	void dfs(int v, int p) {
		up[v] = D();
		for (auto e : adj[v]) {
			int w = e;
			if (w != p) {
				dfs(w, v);
				pref[w] = up[v];
				up[v] = up[v] + up[w];
			} else {
				par[v] = e;
			}
		}
		dp[v] = up[v];
		if (p != -1) {
			up[v] = up[v].up(par[v]);
		}
	}
	void dfs2(int v, int p, D f) {
		for (int j = int(adj[v].size())-1; j >= 0; j--) {
			auto e = adj[v][j];
			int w = e;
			if (w == p) continue;
			dp2[w] = f + pref[w];
			dfs2(w, v, dp2[w].up(e));
			f = f + up[w];
		}
		res[v] = f;
	}
	treedp(const VV<E>& adj_) : adj(adj_), n(int(adj.size())), 
	up(n), pref(n), dp(n), dp2(n), res(n), par(n) {
		assert(n >= 1);
		dfs(0, -1);
		dfs2(0, -1, D());
	}
};
