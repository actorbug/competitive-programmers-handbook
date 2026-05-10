#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	template<class T, class U>
	map<T, ll> grundy(const T& init, U func) {
		map<T, ll> cache;
		auto rec = [&](this auto self, const T& s) -> ll {
			if (cache.contains(s))
				return cache[s];
			auto n = func(s) | views::transform([&](const T& i) { return self(i); }) | ranges::to<unordered_set>();
			for (ll i = 0; ; ++i) {
				if (!n.contains(i)) {
					cache[s] = i;
					return i;
				}
			}
			};
		rec(init);
		return cache;
	}

	vector<vector<ll>> grundy_maze(const pair<ll, ll>& init, const vector<string>& m) {
		auto maze = [&](const pair<ll, ll>& s) {
			auto [y, x] = s;
			vector<pair<ll, ll>> ret;
			for (ll y1 = y - 1; y1 >= 0; --y1) {
				if (m[y1][x] == '#')
					break;
				ret.emplace_back(y1, x);
			}
			for (ll x1 = x - 1; x1 >= 0; --x1) {
				if (m[y][x1] == '#')
					break;
				ret.emplace_back(y, x1);
			}
			return ret;
			};
		vector<vector<ll>> r(m.size(), vector<ll>(m[0].size(), -1));
		for (const auto& [p, v] : grundy(init, maze)) {
			auto [y, x] = p;
			r[y][x] = v;
		}
		return r;
	}
}

TEST(C253SpragueGrundyTheorem, grundy) {
	EXPECT_EQ(grundy(5ll, [](ll s) { return vector<vector<ll>>{{},{0},{1},{0,1},{1,3},{1,4}}[s]; }), (map<ll, ll>{{0,0},{1,1},{3,2},{4,0},{5,2}}));
}

TEST(C253SpragueGrundyTheorem, grundyMaze) {
	EXPECT_EQ(grundy_maze({4,4}, {"..#..","#...#","..#..","#....","....."}), (vector<vector<ll>>{{0,1,-1,0,-1},{-1,0,1,2,-1},{0,2,-1,1,0},{-1,3,0,4,1},{0,4,1,3,2}}));
}
