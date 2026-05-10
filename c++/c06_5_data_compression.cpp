#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct Node;
	using Tree = variant<char, shared_ptr<Node>>;
	struct Node {
		Tree left, right;
	};

	using Dict = unordered_map<char, string>;

	Tree huffman(const string& s) {
		struct HeapNode {
			ll v;
			Tree n;
		};
		unordered_map<char, ll> freq;
		for (char c : s)
			++freq[c];
		priority_queue<HeapNode, vector<HeapNode>, decltype([](const auto& a, const auto& b) { return a.v > b.v; })> heap;
		for (auto [k, v] : freq)
			heap.emplace(v, k);
		if (heap.size() < 2)
			heap.emplace(0, '\0');
		while (heap.size() > 1) {
			auto [v2, k2] = heap.top();
			heap.pop();
			auto [v1, k1] = heap.top();
			heap.pop();
			heap.emplace(v1 + v2, make_shared<Node>(k1, k2));
		}
		return heap.top().n;
	}

	Dict tree2dict(Tree tree) {
		Dict dict;
		auto dfs = [&](this auto self, Tree k, string v) -> void {
			if (k.index() == 0)
				dict[get<0>(k)] = move(v);
			else {
				auto node = get<1>(k);
				self(node->left, v + "0");
				self(node->right, v + "1");
			}
			};
		dfs(tree, "");
		return dict;
	}

	string encode(const string& s, const Dict& d) {
		string ret;
		for (char c : s)
			ret += d.at(c);
		return ret;
	}

	string decode(const string& e, Tree t) {
		string s;
		Tree p = t;
		for (char c : e) {
			auto node = get<1>(p);
			p = (c == '0') ? node->left : node->right;
			if (p.index() == 0) {
				s += get<0>(p);
				p = t;
			}
		}
		return s;
	}
}

TEST(C065DataCompression, encodedecode) {
	auto t = huffman("");
	auto s = encode("", tree2dict(t));
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(decode(s, t), "");
	t = huffman("AAA");
	s = encode("AAA", tree2dict(t));
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(decode(s, t), "AAA");
	t = huffman("AABACDACA");
	s = encode("AABACDACA", tree2dict(t));
	EXPECT_EQ(s.size(), 15);
	EXPECT_EQ(decode(s, t), "AABACDACA");
}
