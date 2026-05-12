#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct record {
		string task;
		ll duration;
		ll deadline;
		bool operator==(const record&) const = default;
	};

	vector<record> solve(vector<record> ary) {
		ranges::sort(ary, {}, &record::duration);
		return ary;
	}

	ll score(const vector<record>& ary) {
		ll cur = 0, sc = 0;
		for (auto& r : ary) {
			cur += r.duration;
			sc += r.deadline - cur;
		}
		return sc;
	}
}

TEST(C063TasksAndDeadlines, solve) {
	EXPECT_EQ(score(solve({})), 0);
	EXPECT_EQ(score(solve({ {"A",4,2},{"B",3,5},{"C",2,7},{"D",4,5} })), -10);
}
