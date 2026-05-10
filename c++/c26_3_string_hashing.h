#pragma once

template<ll A = 911382323, ll B = 972663749>
struct Preprocessing {
	Preprocessing(const string& s) : s{ s }, h{ 0 }, p{ B - 1 } {
		for (char c : s) {
			h.push_back((h.back() * A + c) % B);
			p.push_back(p.back() * A % B);
		}
	}
	bool operator==(const Preprocessing& o) const {
		return s == o.s;
	}
	ll size() const {
		return ssize(s);
	}
	ll subhash(ll l, ll r) const {
		return (h[l] * p[r - l] % B + h[r]) % B;
	}
	auto operator<=>(const Preprocessing& o) const {
		ll ok = 0, ng = min(size(), o.size()) + 1;
		while (ng - ok > 1) {
			ll mid = (ok + ng) / 2;
			if (subhash(0, mid) == o.subhash(0, mid))
				ok = mid;
			else
				ng = mid;
		}
		if (ok >= size() || ok >= o.size())
			return size() <=> o.size();
		else
			return s[ok] <=> o.s[ok];
	}
	ll find(const string& t) const {
		ll n = ssize(t), ht = hash(t);
		for (ll i = 0; i < ssize(s) - n + 1; ++i) {
			if (subhash(i, i + n) == ht && s.substr(i, n) == t) {
				return i;
			}
		}
		return -1;
	}
	static ll hash(const string& s) {
		return Preprocessing(s).h.back();
	}
	string s;
	vector<ll> h, p;
};
