#pragma once

ll ipow(ll x, ll n);
ll isqrt(ll x);
ll comb(ll n, ll r);
bool next_product(vector<ll>& vec, ll n);
vector<vector<ll>> reversed_adj(const vector<vector<ll>>& adj);
vector<vector<ll>> delweight(const vector<vector<pair<ll, ll>>>& adj);
bool equal_adj(const vector<vector<ll>>& adj1, const vector<vector<ll>>& adj2);
