/**
 * Author: Hanfei Chen
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: tested on https://judge.yosupo.jp/submission/112531, https://judge.yosupo.jp/submission/112532
 */
#pragma once

template <class T> /// start-hash
void fst(vector<T>& a, bool inv) {
	int n = sz(a);
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
			for (int j = 0; j < k; j++) {
				T &u = a[i+j], &v = a[i+j+k];
				tie(u, v) = 
					inv ? make_pair(v - u, u) : make_pair(v, u + v); // AND
					inv ? make_pair(v, u - v) : make_pair(u + v, u); // OR
					make_pair(u + v, u - v);						 // XOR
			}
		}
	}
	if (inv) for (T& x : a) x /= n; // XOR only
} /// end-hash

template <class T> /// start-hash
vector<T> conv(vector<T> a, vector<T> b) {
	fst(a, false);
	fst(b, false);
	rep(i,0,sz(a)) a[i] *= b[i];
	fst(a, true);
	return a;
} /// end-hash
