/**
 * Author: Hanfei Chen
 * Description: Cartesian tree. The minimum becomes the root.
 */

#pragma once

/// start-hash
template <class T> struct cartesian {
	int n, rt;
	vi par, lch, rch;
	cartesian(const V<T>& a) : n(sz(a)), rt(0), 
	par(n, -1), lch(n, -1), rch(n, -1) {
		assert(n >= 1);
		vi stk = {0};
		stk.reserve(n);
		rep(i,1,n) {
			if (a[stk.back()] > a[i]) {
				while (stk.size() >= 2 && a[stk.end()[-2]] > a[i]) {
					stk.pop_back();
				}
				if (stk.size() == 1) {
					rt = par[lch[i] = stk.back()] = i;
				} else {
					par[lch[i] = stk.back()] = i;
					rch[par[i] = stk.end()[-2]] = i;
				}
				stk.back() = i;
			} else {
				rch[par[i] = stk.back()] = i;
				stk.push_back(i);
			}
		}
	}
};
/// end-hash
