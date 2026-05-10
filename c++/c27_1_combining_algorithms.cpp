#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	constexpr pair<ll, ll> dv[] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
	optional<pair<pair<ll, ll>, pair<ll, ll>>> min_dist(const vector<string>& board) {
		ll h = ssize(board), w = board.empty() ? 0 : ssize(board[0]), n = w * h, mind = w + h;
		optional<pair<pair<ll, ll>, pair<ll, ll>>> minp;
		auto algorithm1 = [&](const vector<pair<ll, ll>>& ps) {
			for (ll i = 0; i < ssize(ps) - 1; ++i) {
				auto [y1, x1] = ps[i];
				for (ll j = i + 1; j < ssize(ps); ++j) {
					auto [y2, x2] = ps[j];
					ll md = abs(y2 - y1) + abs(x2 - x1);
					if (mind > md) {
						mind = md;
						minp = { {y1, x1}, {y2, x2} };
					}
				}
			}
			};
		auto algorithm2 = [&](const vector<pair<ll, ll>>& ps) {
			queue<pair<ll, ll>> q(ps | ranges::to<deque>());
			vector<vector<pair<ll, ll>>> info(h, vector<pair<ll, ll>>(w, { -1, -1 }));
			for (ll i = 0; i < ssize(ps); ++i) {
				auto [y, x] = ps[i];
				info[y][x] = { i, 0 };
			}
			while (!q.empty()) {
				auto [y, x] = q.front(); q.pop();
				for (auto [dy, dx] : dv) {
					ll ny = y + dy, nx = x + dx;
					if (ny < 0 || h <= ny || nx < 0 || w <= nx || info[ny][nx].first == info[y][x].first)
						continue;
					if (info[ny][nx].first < 0) {
						info[ny][nx] = { info[y][x].first, info[y][x].second + 1 };
						q.emplace(ny, nx);
						continue;
					}
					ll md = info[y][x].second + info[ny][nx].second + 1;
					if (mind > md) {
						mind = md;
						minp = { ps[info[y][x].first], ps[info[ny][nx].first] };
					}
				}
			}
			};
		unordered_map<char, vector<pair<ll, ll>>> d;
		for (ll i = 0; i < h; ++i) {
			for (ll j = 0; j < w; ++j) {
				d[board[i][j]].emplace_back(i, j);
			}
		}
		for (const auto& [_, ps] : d) {
			if (ssize(ps) * ssize(ps) <= n)
				algorithm1(ps);
			else
				algorithm2(ps);
		}
		return minp;
	}

	vector<ll> min_dist2(const vector<pair<ll, ll>>& pos) {
		ll h = ranges::max(pos | views::keys) + 1, w = ranges::max(pos | views::values) + 1;
		ll m = 1 + isqrt(max<ll>(ssize(pos) - 1, 0ll));
		vector<ll> ret;
		vector<pair<ll, ll>> rest;
		vector<vector<ll>> board;
		for (ll i = 0; i < ssize(pos); ++i) {
			auto [y, x] = pos[i];
			if (i > 0) {
				ret.push_back(board[y][x]);
				for (auto [y1, x1] : rest)
					ret.back() = min(ret.back(), abs(y - y1) + abs(x - x1));
			}
			if (i % m) {
				rest.emplace_back(y, x);
				continue;
			}
			queue<pair<ll, ll>> q(pos.begin(), pos.begin() + i + 1);
			board.assign(h, vector<ll>(w, -1));
			for (ll j = 0; j <= i; ++j) {
				auto [y, x] = pos[j];
				board[y][x] = 0;
			}
			while (!q.empty()) {
				auto [y, x] = q.front(); q.pop();
				for (auto [dy, dx] : dv) {
					ll ny = y + dy, nx = x + dx;
					if (ny < 0 || h <= ny || nx < 0 || w <= nx)
						continue;
					if (board[ny][nx] < 0) {
						board[ny][nx] = board[y][x] + 1;
						q.emplace(ny, nx);
					}
				}
			}
			rest.clear();
		}
		return ret;
	}
}

TEST(C271CombiningAlgorithms, minDist) {
	EXPECT_EQ(min_dist({}), nullopt);
	EXPECT_EQ(min_dist({"AA"}), (pair<pair<ll, ll>, pair<ll, ll>>{{0,0}, {0,1}}));
	EXPECT_EQ(min_dist({"AFBA", "CEGE", "BDAF", "ACBD"}), (pair<pair<ll, ll>, pair<ll, ll>>{{1,1}, {1,3}}));
	EXPECT_EQ(min_dist({"AFBA", "CHGE", "BDAF", "ACBA"}), (pair<pair<ll, ll>, pair<ll, ll>>{{3,3}, {2,2}}));
	EXPECT_EQ(min_dist({"ABCD", "EFGH", "IJKL", "MNOP"}), nullopt);
}

TEST(C271CombiningAlgorithms, minDist2) {
	EXPECT_EQ(min_dist2({{0,0},{2,3},{2,1},{0,2},{3,0},{3,2},{0,1},{0,3},{1,0},{1,1},{1,2},{1,3},{2,0},{2,2},{3,1},{3,3}}), (vector<ll>{5,2,2,2,2,1,1,1,1,1,1,1,1,1,1}));
}
