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
}

TEST(C062Scheduling, solve) {
	EXPECT_EQ(solve({}), (vector<record>{}));
	EXPECT_EQ(solve({ {"A",1,3},{"B",2,5},{"C",3,9},{"D",6,8} }), (vector<record>{ {"A",1,3}, {"D",6,8} }));
	EXPECT_EQ(solve({ {"A",1,4},{"B",3,5},{"C",4,7} }), (vector<record>{ {"A",1,4}, {"C",4,7} }));
	EXPECT_EQ(solve({ {"A",1,7},{"B",2,4},{"C",4,6} }), (vector<record>{ {"B",2,4}, {"C",4,6} }));
}
