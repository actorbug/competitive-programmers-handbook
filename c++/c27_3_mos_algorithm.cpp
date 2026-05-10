#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	void dec(unordered_map<ll, ll>& count, ll i) {
		--count[i];
		if (count[i] <= 0)
			count.erase(i);
	}
	vector<ll> mo(const vector<ll>& array, const vector<pair<ll, ll>>& q) {
		ll m = isqrt(max<ll>(ssize(array) - 1, 0ll)) + 1;
		unordered_map<ll, ll> count;
		vector<ll> ret(q.size());
		ll b = 0, e = 0;
		auto s = views::iota(0ll, ssize(q)) | views::transform([&](ll i) { return make_tuple(q[i].first / m, q[i].second, i); }) | ranges::to<vector>();
		ranges::sort(s);
		for (auto [_1, _2, i] : s) {
			auto [l, r] = q[i];
			if (b == e)
				b = e = l;
			while (e < r)
				++count[array[e++]];
			while (e > r)
				dec(count, array[--e]);
			while (b > l)
				++count[array[--b]];
			while (b < l)
				dec(count, array[b++]);
			ret[i] = ssize(count);
		}
		return ret;
	}
}

TEST(C273MosAlgorithm, mo) {
	EXPECT_EQ(mo({}, {}), vector<ll>{});
	EXPECT_EQ(mo({ 4,2,5,4,2,4,3,3,4 }, { {1,5},{2,7} }), (vector<ll>{ 3,4 }));
}
