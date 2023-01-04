/**
 * Author: Hanfei Chen
 * Date: 2023-01-03
 * Description: You do not need to keep writing $\%\, mod$ stuff.
 * Status: used a lot so it should be good?
 */
#pragma once

template <class T> T pow(T a, ll b) {
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1, a *= a; } return r;
}

/// start-hash
template <int MOD> struct mint {
	static constexpr int m = MOD;

	int v;
	mint() : v(0) {}
	mint(ll v_) : v(int(v_ % m)) { if (v < 0) v += m; }
	explicit operator int() const { return v; }
	friend mint inv(const mint& n) { return pow(n, m-2); }

	mint& operator += (const mint& o) { v -= m-o.v; if (v < 0) v += m; return *this; }
	mint& operator -= (const mint& o) { v -= o.v; if (v < 0) v += m; return *this; }
	mint& operator *= (const mint& o) { v = int(ll(v) * o.v % m); return *this; }
	mint& operator /= (const mint& o) { return *this *= inv(o); }

	friend mint operator + (const mint &a, const mint & b) { return mint(a) += b; }
	friend mint operator - (const mint &a, const mint & b) { return mint(a) -= b; }
	friend mint operator * (const mint &a, const mint & b) { return mint(a) *= b; }
	friend mint operator / (const mint &a, const mint & b) { return mint(a) /= b; }
};
/// end-hash