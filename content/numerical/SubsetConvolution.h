/**
 * Author: Hanfei Chen
 * Description: Subset Convolution of array $a$ and $b$. 
 * Resulting array $c$ satisfies $c_z = \sum_{x, y:\, x | y = z, x \& y = 0} a_x \cdot b_y$. 
 * Length of $a$ and $b$ should be same and be a power of $2$.
 * Time: O(N \log^2 N)
 * Status: tested on https://judge.yosupo.jp/submission/112611
 */
#pragma once

#include "FastSubsetTransform.h"

template <class T>
vector<T> subset_conv(const vector<T>& a, const vector<T>& b) {
	int n = sz(a);
	assert(n > 0 && sz(b) == n);
	int l = __lg(n);
	vector<vector<T>> sa(l+1, vector<T>(n));
	rep(i,0,n) sa[__builtin_popcount(i)][i] = a[i];
	// fst: OR transform
	for (auto& x : sa) fst(x, false);
	vector<vector<T>> sb(l+1, vector<T>(n));
	rep(i,0,n) sb[__builtin_popcount(i)][i] = b[i];
	for (auto& x : sb) fst(x, false);
	vector<vector<T>> sc(l+1, vector<T>(n));
	rep(x,0,l+1) rep(y,0,l-x+1) {
		rep(i,0,n) sc[x+y][i] += sa[x][i] * sb[y][i];
	}
	for (auto& x : sc) fst(x, true);
	vector<T> c(n);
	rep(i,0,n) c[i] = sc[__builtin_popcount(i)][i];
	return c;
}
