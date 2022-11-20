/**
 * Author: Hanfei Chen
 * Date: 2022-10-29 
 * Description: You do not need to keep writing $\%\, mod$ stuff.
 * Status: used a lot so it should be good?
 */
#pragma once

template <class T> T pow(T a, ll b) { /// start-hash
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1, a *= a; } return r;
} /// end-hash

template <int MOD_> struct Z { /// start-hash
	static constexpr int MOD = MOD_;

	int v;
	Z() : v(0) {}
	Z(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend Z inv(const Z& n) { return pow(n, MOD-2); }

	Z& operator += (const Z& o) { v -= MOD-o.v; if (v < 0) v += MOD; return *this; }
	Z& operator -= (const Z& o) { v -= o.v; if (v < 0) v += MOD; return *this; }
	Z& operator *= (const Z& o) { v = int(ll(v) * o.v % MOD); return *this; }
	Z& operator /= (const Z& o) { return *this *= inv(o); }

	friend Z operator + (const Z &a, const Z & b) { return Z(a) += b; }
	friend Z operator - (const Z &a, const Z & b) { return Z(a) -= b; }
	friend Z operator * (const Z &a, const Z & b) { return Z(a) *= b; }
	friend Z operator / (const Z &a, const Z & b) { return Z(a) /= b; }
}; /// end-hash
