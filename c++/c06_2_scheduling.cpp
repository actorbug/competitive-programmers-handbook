#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct record {
		string event;
		ll start;
		ll end;
		bool operator==(const record&) const = default;
	};

	vector<record> solve(vector<record> ary) {
		vector<record> ret;
		ll end = 0;
		ranges::sort(ary, {}, &record::end);
		for (auto& r : ary) {
			if (r.start >= end) {
				ret.push_back(r);
				end = r.end;
			}
		}
		return ret;
	}

	void test(const vector<record>& ary, ll l) {
		auto ret = solve(ary);
		EXPECT_EQ(ret.size(), l);
		ranges::sort(ret, {}, &record::start);
		for (const auto& [a, b] : ret | views::pairwise)
			EXPECT_LE(a.end, b.start);
	}
}

TEST(C062Scheduling, solve) {
	test({}, 0);
	test({ {"A",1,3},{"B",2,5},{"C",3,9},{"D",6,8} }, 2);
	test({ {"A",1,4},{"B",3,5},{"C",4,7} }, 2);
	test({ {"A",1,7},{"B",2,4},{"C",4,6} }, 2);
}
