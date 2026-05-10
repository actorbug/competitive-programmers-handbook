#pragma once

template<typename T>
struct MinimumQueries {
	MinimumQueries(const vector<T>& array) : m(bit_width(array.size())) {
		ll n = ssize(array);
		m[0] = array;
		for (ll i = 1; i < ssize(m); ++i) {
			for (ll j = 0; j < n - (1ll << i) + 1; ++j) {
				m[i].push_back(min(m[i - 1][j], m[i - 1][j + (1ll << (i - 1))]));
			}
		}
	}
	T operator()(ll a, ll b) const {
		ll k = bit_width(ull(b - a + 1)) - 1;
		return min(m[k][a], m[k][b - (1ll << k) + 1]);
	}
private:
	vector<vector<T>> m;
};
