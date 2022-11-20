/**
 * Author: Hanfei Chen
 * Date: 2022-11-19 
 * Description: Given two integers $a$ and $b$, finds two integers $x$ and $y$ such that $ax+by=\gcd(a,b)$.
 */
#pragma once

template <class T> pair<T, T> euclid(T a, T b) {
	if (b == 0) {
		return {1, 0};
	}
	auto [x, y] = euclid(b, a % b);
	return {y, x - a / b * y};
}
