/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Time: O(N)
 * Status: Fuzz-tested
 */
#pragma once

template <class S> array<vi, 2> manacher(const S& s) {
	int n = sz(s);
	array<vi, 2> p = {vi(n+1), vi(n)};
	rep(z,0,2) {
		int l = 0, r = 0;
		rep(i,0,n) {
			int t = r-i + !z;
			int& k = p[z][i];
			if (i < r) k = min(t, p[z][l+t]);
			int nl = i-k;
			int nr = i+k - !z;
			while (nl-1 >= 0 && nr+1 < n && s[nl-1] == s[nr+1]) {
				k++;
				nl--, nr++;
			}
			if (nr > r) {
				l = nl, r = nr;
			}
		}
	}
	return p;
}
