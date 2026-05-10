#pragma once
#include "c09_2_binary_indexed_tree.h"

template<typename T>
unordered_map<T, ll> index_compression(vector<T> array, ll start = 0) {
	unordered_map<T, ll> ret;
	ranges::sort(array);
	for (T i : array)
		if (!ret.contains(i))
			ret[i] = start++;
	return ret;
}

struct RangeUpdates {
	RangeUpdates(ll n) : bit(n + 1) {}
	RangeUpdates(const vector<ll>& ary) : bit(init(ary)) {}
	ll operator[](ll k) const {
		return bit.sum(k + 1);
	}
	void add(ll a, ll b, ll x) {
		bit.add(a + 1, x);
		bit.add(b + 2, -x);
	}
private:
	static vector<ll> init(const vector<ll>& ary) {
		vector<ll> ret(ary.size() + 1);
		for (ll i = 0; i < ssize(ret); ++i)
			ret[i] = ((i < ssize(ret) - 1) ? ary[i] : 0) - ((i > 0) ? ary[i - 1] : 0);
		return ret;
	}
	BIT bit;
};
