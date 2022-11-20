/**
 * Author: Hanfei Chen
 * Description: Linear Time Suffix Array
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/SuffixArrayLinear.h
 */
#pragma once

vi sa_is(const vi& s, int upper) {
	int n = sz(s);
	if (!n) return {};
	vi sa(n); vector<bool> ls(n);
	per(i,0,n-1) ls[i] = s[i] == s[i+1] ? ls[i+1] : s[i] < s[i+1];
	vi sum_l(upper), sum_s(upper);
	rep(i,0,n) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++;
	rep(i,0,upper) {
		if (i) sum_l[i] += sum_s[i-1];
		sum_s[i] += sum_l[i];
	}
	auto induce = [&](const vi& lms) {
		fill(all(sa), -1);
		vi buf = sum_s;
		for (int d : lms) if (d != n) sa[buf[s[d]]++] = d;
		buf = sum_l; sa[buf[s[n-1]]++] = n-1;
		rep(i,0,n) {
			int v = sa[i]-1;
			if (v >= 0 && !ls[v]) sa[buf[s[v]]++] = v;
		}
		buf = sum_l;
		per(i,0,n) {
			int v = sa[i]-1;
			if (v >= 0 && ls[v]) sa[--buf[s[v]+1]] = v;
		}
	};
	vi lms_map(n+1, -1), lms; int m = 0;
	rep(i,1,n) if (!ls[i-1] && ls[i]) lms_map[i] = m++, lms.push_back(i);
	induce(lms);
	vi sorted_lms;
	for (int v : sa) if (lms_map[v] != -1) sorted_lms.push_back(v);
	vi rec_s(m); int rec_upper = 0;
	rep(i,1,m) {
		int l = sorted_lms[i-1], r = sorted_lms[i];
		int end_l = lms_map[l]+1 < m ? lms[lms_map[l]+1] : n;
		int end_r = lms_map[r]+1 < m ? lms[lms_map[r]+1] : n;
		bool same = false;
		if (end_l-l == end_r-r) {
			for (; l < end_l && s[l] == s[r]; l++, r++) {}
			if (l != n && s[l] == s[r]) same = true;
		}
		rec_s[lms_map[sorted_lms[i]]] = (rec_upper += !same);
	}
	vi rec_sa = sa_is(rec_s, rec_upper+1);
	rep(i,0,m) sorted_lms[i] = lms[rec_sa[i]];
	induce(sorted_lms);
	return sa;
}
