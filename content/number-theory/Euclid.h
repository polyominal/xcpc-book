/**
 * Author: Hanfei Chen
 * Date: 2023-01-03
 * Source: https://cp-algorithms.com/algebra/linear-diophantine-equation.html
 * Description: $ax + by = c$ stuff.
 */
#pragma once

/// start-hash
tuple<ll, ll, ll> euclid(ll a, ll b) {
	if (b == 0) {
		return {1, 0, a};
	}
	auto [x, y, g] = euclid(b, a % b);
	return {y, x - a / b * y, g};
}
/// end-hash

template <class T, class U> U fix(T a, U m) {
	a %= m;
	if (a < 0) a += m;
	return U(a);
}

/// start-hash
ll minv(ll a, ll m) {
	a %= m;
	auto [x, y, g] = euclid(a, m);
	if (g != 1) return -1;
	return fix(x, m);
}
/// end-hash

/// start-hash
// NOT tested, but anyway
pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2) {
	auto [x, y, g] = euclid(m1, m2);
	if (a1 % g != a2 % g) return {0, -1};
	x = fix(__int128_t(x) * a2, m2);
	y = fix(__int128_t(y) * a1, m1);
	ll lcm = m1 * (m2 / g);
	return {fix(__int128_t(x) * (m1/g) + __int128_t(y) * (m2/g), lcm), lcm};
}
/// end-hash

// returns g == -1 if no solution
/// start-hash
tuple<ll, ll, ll> find_any(ll a, ll b, ll c) {
	auto [x0, y0, g] = euclid(abs(a), abs(b));
	if (c % g) return {-1, -1, -1};
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 = -x0;
	if (b < 0) y0 = -y0;
	return {x0, y0, g};
}
/// end-hash

void shift(ll& x, ll& y, ll a, ll b, ll cnt) {
	x += cnt * b;
	y -= cnt * a;
}

// # of (x, y) with xmin <= x and x <= xmax and ymin <= y and y <= ymax
/// start-hash
ll count_sols(ll a, ll b, ll c, ll xmin, ll xmax, ll ymin, ll ymax) {
	auto [x, y, g] = find_any(a, b, c);
	if (g == -1) return 0;

	a /= g, b /= g;
	int sgn_a = (a > 0) - (a <= 0);
	int sgn_b = (b > 0) - (b <= 0);

	shift(x, y, a, b, (xmin - x) / b);
	if (x < xmin) shift(x, y, a, b, sgn_b);
	if (x > xmax) return 0;
	ll lx1 = x;
	shift(x, y, a, b, (xmax - x) / b);
	if (x > xmax) shift(x, y, a, b, -sgn_b);
	ll rx1 = x;

	shift(x, y, a, b, -(ymin - y) / a);
	if (y < ymin) shift(x, y, a, b, -sgn_a);
	if (y > ymax) return 0;
	ll lx2 = x;
	shift(x, y, a, b, -(ymax - y) / a);
	if (y > ymax) shift(x, y, a, b, sgn_a);
	ll rx2 = x;

	if (lx2 > rx2) swap(lx2, rx2);
	ll lx = max(lx1, lx2);
	ll rx = min(rx1, rx2);
	if (lx > rx) return 0;
	return (rx - lx) / abs(b) + 1;
}
/// end-hash