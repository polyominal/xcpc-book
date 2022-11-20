/**
 * Author: Hanfei Chen 
 * Date: 2022-11-18
 * Description: DSU that supports undo operation. Use cp = checkpoint() to get a checkpoint, and undo(cp) to get back to the checkpoint cp.
 * Time: $O(\log(N))$
 * Status: tested on https://codeforces.com/gym/104022/submission/181368795
 */
#pragma once

struct UndoDSU {
	using G = int;
	// some global variable, we take # of components as an example
	G global;

	struct D {
		// # of vertices in the same component for example
		int num;
		D() : num(1) {}
	};

	void join(D& a, const D& b) {
		a.num += b.num;
		// also maintain global variable here
		global--;
	}

	int n;
	vector<D> data;
	vector<int> par;
	vector<tuple<int, int, D, G>> stk;

	UndoDSU(int n_) {
		init(n_);
	}

	void init(int n_) {
		n = n_;
		data = vector<D>(n);
		par = vector<int>(n, -1);
		stk.clear();
		// initialize global variable here
		global = n;
	}

	/// start-hash
	int getpar(int a) {
		while (par[a] >= 0) a = par[a];
		return a;
	}

	bool merge(int a, int b) {
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		a = getpar(a);
		b = getpar(b);
		if (a == b) return false;
		if (par[a] > par[b]) swap(a, b);
		stk.emplace_back(par[b], b, data[a], global);
		par[a] += par[b];
		par[b] = a;
		join(data[a], data[b]);
		return true;
	}

	int checkpoint() {
		return sz(stk);
	}

	void undo(int cp) {
		while (sz(stk) > cp) {
			auto& [pb, b, d, g] = stk.back();
			stk.pop_back();
			int a = par[b];
			par[b] = pb;
			par[a] -= pb;
			data[a] = d;
			global = g;
		}
	}
	/// end-hash
};

