#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct Trie {
		Trie() : v(1), last() {}
		void add(const string& s) {
			ll cur = 0;
			for (char c : s) {
				if (v[cur].contains(c))
					cur = v[cur][c];
				else {
					v[cur][c] = ssize(v);
					cur = ssize(v);
					v.resize(v.size() + 1);
				}
			}
			last.insert(cur);
		}
		bool contains(const string& s) {
			ll cur = 0;
			for (char c : s) {
				if (!v[cur].contains(c))
					return false;
				cur = v[cur][c];
			}
			return last.contains(cur);
		}
		string prefix(const string& s) {
			ll l = 0, cur = 0;
			for (ll i = 0; i < ssize(s); ++i) {
				if (!v[cur].contains(s[i]))
					return s.substr(0, l);
				cur = v[cur][s[i]];
				if (last.contains(cur))
					l = i + 1;
			}
			return s.substr(0, l);
		}
	private:
		vector<unordered_map<char, ll>> v;
		unordered_set<ll> last;
	};
}

TEST(C262TrieStructure, Trie) {
	Trie t;
	t.add("CANAL");
	t.add("CANDY");
	t.add("THE");
	t.add("THERE");
	EXPECT_FALSE(t.contains("THERN"));
	EXPECT_TRUE(t.contains("THE"));
	EXPECT_EQ(t.prefix("THERN"), "THE");
}
