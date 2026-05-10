#pragma once

struct UnionFind {
	UnionFind(ll n) : link(n, -1) {}
	ll find(ll x) const {
		if (link[x] < 0) return x;
		return link[x] = find(link[x]);
	}
	bool same(ll a, ll b) const {
		return find(a) == find(b);
	}
	void unite(ll a, ll b) {
		a = find(a);
		b = find(b);
		if (a != b) {
			if (link[a] > link[b])
				swap(a, b);
			link[a] += link[b];
			link[b] = a;
		}
	}
private:
	mutable vector<ll> link;
};
