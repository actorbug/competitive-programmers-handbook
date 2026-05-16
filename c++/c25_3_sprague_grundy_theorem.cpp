#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	template<class T, class U>
	map<T, ll> grundy(const vector<T>& states, U func) {
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
		for (const auto& s : states)
			rec(s);
		return cache;
	}

	vector<vector<ll>> grundy_maze(const vector<string>& m) {
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
		ll h = ssize(m), w = ssize(m[0]);
		vector<vector<ll>> r(h, vector<ll>(w, -1));
		vector<pair<ll, ll>> states;
		for (ll i = 0; i < h; ++i) {
			for (ll j = 0; j < w; ++j) {
				if (m[i][j] != '#') {
					states.emplace_back(i, j);
				}
			}
		}
		for (const auto& [p, v] : grundy(states, maze)) {
			auto [y, x] = p;
			r[y][x] = v;
		}
		return r;
	}
}

TEST(C253SpragueGrundyTheorem, grundy) {
	EXPECT_EQ(grundy<ll>({ 0,1,2,3,4,5 }, [](ll s) { return vector<vector<ll>>{{},{0},{1},{0,1},{1,3},{1,4}}[s]; }), (map<ll, ll>{{0,0},{1,1},{2,0},{3,2},{4,0},{5,2}}));
}

TEST(C253SpragueGrundyTheorem, grundyMaze) {
	EXPECT_EQ(grundy_maze({"..#..","#...#","..#..","#....","....."}), (vector<vector<ll>>{{0,1,-1,0,1},{-1,0,1,2,-1},{0,2,-1,1,0},{-1,3,0,4,1},{0,4,1,3,2}}));
}
