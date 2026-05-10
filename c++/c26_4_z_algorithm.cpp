#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<ll> zalgorithm(string s) {
		ll n = ssize(s);
		vector<ll> z(n);
		ll x = 0, y = 0;
		for (ll i = 1; i < n; ++i) {
			z[i] = max(0ll, min(z[i - x], y - i + 1));
			while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
				x = i; y = i + z[i]; ++z[i];
			}
		}
		return z;
	}

	ll find(const string& s, const string& t) {
		ll n = ssize(t);
		if (n <= 0)
			return 0;
		auto z = zalgorithm(t + "#" + s);
		auto i = ::find(z.begin() + n + 1, z.end(), n);
		if (i == z.end())
			return -1;
		return i - z.begin() - n - 1;
	}
}

TEST(C264ZAlgorithm, zalgorithm) {
	EXPECT_EQ(zalgorithm(""), vector<ll>{});
	EXPECT_EQ(zalgorithm("ACBACDACBACBACDA"), (vector<ll>{0,0,0,2,0,0,5,0,0,7,0,0,2,0,0,1}));
}

TEST(C264ZAlgorithm, find) {
	EXPECT_EQ(find("", ""), 0);
	EXPECT_EQ(find("HATTIVATTI", "ATT"), 1);
	EXPECT_EQ(find("HATTIVATTI", "XXX"), -1);
}
