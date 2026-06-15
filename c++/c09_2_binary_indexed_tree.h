#pragma once

struct BIT {
	BIT(size_t n) : tree(n + 1) {}
	BIT(const vector<ll>& ary) : tree(ary.size() + 1) {
		ranges::copy(ary, tree.begin() + 1);
		ll j, n = ssize(tree);
		for (ll i = 0; i < n; ++i) {
			if ((j = i + (i & -i)) < n) {
				tree[j] += tree[i];
			}
		}
	}
	ll operator[](ll k) const {
		return sum(k) - sum(k - 1);
	}
	ll sum(ll k) const {
		ll s = 0;
		while (k >= 1) {
			s += tree[k];
			k -= k & -k;
		}
		return s;
	}
	ll lower_bound(ll x) const {
		ll size = ssize(tree) - 1;
		ll sum = 0, pos = 0;
		for (ll i = bit_width(ull(size)); i >= 0; --i) {
			ll k = pos + (1ll << i);
			if (k <= size && sum + tree[k] < x) {
				sum += tree[k];
				pos += 1ll << i;
			}
		}
		return pos + 1;
	}
	void set(ll k, ll x) {
		add(k, x - (*this)[k]);
	}
	void add(ll k, ll x) {
		while (k < ssize(tree)) {
			tree[k] += x;
			k += k & -k;
		}
	}
private:
	vector<ll> tree;
};
