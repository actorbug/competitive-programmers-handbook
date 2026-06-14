#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct Delete {
		ll pos;
		char c;
		bool operator==(const Delete&) const = default;
	};
	struct Add {
		ll pos;
		char c;
		bool operator==(const Add&) const = default;
	};
	struct Edit {
		ll pos;
		char c1, c2;
		bool operator==(const Edit&) const = default;
	};
	using Command = variant<Delete, Add, Edit>;

	vector<Command> solve(string x, string y) {
		vector<vector<ll>> distance(x.size() + 1, vector<ll>(y.size() + 1));
		for (ll a = 0; a <= ssize(x); ++a)
			distance[a][0] = a;
		for (ll b = 0; b <= ssize(y); ++b)
			distance[0][b] = b;
		for (ll a = 1; a <= ssize(x); ++a) {
			for (ll b = 1; b <= ssize(y); ++b) {
				distance[a][b] = min({ distance[a][b - 1] + 1, distance[a - 1][b] + 1, distance[a - 1][b - 1] + (x[a - 1] != y[b - 1]) });
			}
		}
		vector<Command> ret;
		ll a = ssize(x), b = ssize(y);
		while (a > 0 && b > 0) {
			if (a > 0 && distance[a - 1][b] + 1 == distance[a][b]) {
				ret.push_back(Delete{ b, x[a - 1] });
				--a;
			}
			else if (b > 0 && distance[a][b - 1] + 1 == distance[a][b]) {
				ret.push_back(Add{ b - 1, y[b - 1] });
				--b;
			}
			else {
				if (distance[a - 1][b - 1] + 1 == distance[a][b])
					ret.push_back(Edit{ b - 1, x[a - 1], y[b - 1] });
				--a;
				--b;
			}
		}
		ranges::reverse(ret);
		return ret;
	}
}

TEST(C075EditDistance, solve) {
	EXPECT_EQ(solve("", ""), vector<Command>{});
	EXPECT_EQ(solve("ABC", "ABCA"), (vector<Command>{Add{ 3, 'A' }}));
	EXPECT_EQ(solve("ABC", "AC"), (vector<Command>{Delete{ 1, 'B' }}));
	EXPECT_EQ(solve("ABC", "ADC"), (vector<Command>{Edit{ 1, 'B', 'D' }}));
	EXPECT_EQ(solve("LOVE", "MOVIE"), (vector<Command>{Edit{ 0, 'L', 'M' }, Add{ 3, 'I' }}));
}
