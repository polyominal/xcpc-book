/**
 * Author: Hanfei Chen
 * Date: 2022-11-05
 * Source: https://github.com/anroysko/lETHargy-ctl/blob/main/content/graph/costflow-successive-shortest-path.cpp
 * Description: Min-cost max-flow.
 *  You might precompute h[] if possible.
 * Time: O(|F| |E|\log{|E|}) for non-negative costs, where $|F|$ is the size of maximum flow. O(|V| |E| + |F| |E|\log{|E|}) for arbitrary costs.
 */
#pragma once

template <typename F = int, typename C = int64_t,
		 F INF_FLOW = numeric_limits<F>::max() / 2,
		 C INF_COST = numeric_limits<C>::max() / 4>
struct MCMF {
	int n;
	struct E {
		int dest;
		F a;
		C w;
	};
	vector<E> es;
	vector<vi> g;
	vector<C> h;

	explicit MCMF(int n_) : n(n_), g(n) { assert(n >= 2); }

	void add_edge(int a, int b, F cap, C cost) {
		g[a].push_back(sz(es));
		es.push_back({b, cap, cost});
		g[b].push_back(sz(es));
		es.push_back({a, 0, -cost});
	}

	pair<F, C> maxflow(int s, int t, F maxf = INF_FLOW) {
		// run Bellman-Ford if necessary
		if (h.empty()) {
			h = vector<C>(n, INF_COST);
			h[s] = 0;
			rep(z,0,n-1) rep(i,0,n) for (auto e : g[i]) {
				auto [j, c, w] = es[e];
				if (c > 0) h[j] = min(h[j], h[i] + w);
			}
		}
		assert(sz(h) == n);
		F flow = 0;
		C cost = 0;
		while (maxf) {
			priority_queue<pair<C, int>> pq;
			vector<C> dist(n, INF_COST);
			dist[s] = 0;
			pq.emplace(0, s);
			vi prv(n, -1);
			vector<bool> mark(n, false);
			while (sz(pq)) {
				auto [d, cur] = pq.top();
				pq.pop();
				// Using mark[] is safer than comparing -d and dist[cur]
				if (mark[cur]) continue;
				mark[cur] = true;
				for (auto e : g[cur]) {
					auto [nxt, c, w] = es[e];
					C nd = dist[cur] + w + h[cur] - h[nxt];
					if (c > 0 && dist[nxt] > nd) {
						dist[nxt] = nd;
						pq.emplace(-dist[nxt], nxt);
						prv[nxt] = e;
					}
				}
			}
			if (prv[t] == -1) break;
			rep(i,0,n) if (dist[i] != INF_COST) h[i] += dist[i];
			F aug = maxf;
			for (int i = prv[t]; i >= 0; i = prv[es[i^1].dest]) {
				aug = min(aug, es[i].a);
			}
			for (int i = prv[t]; i >= 0; i = prv[es[i^1].dest]) {
				es[i].a -= aug;
				es[i^1].a += aug;
			}
			maxf -= aug;
			flow += aug;
			cost += aug * h[t];
		}
		return {flow, cost};
	}
};
