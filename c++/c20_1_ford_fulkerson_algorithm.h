#pragma once

vector<unordered_map<ll, ll>> edmonds_karp(const vector<vector<pair<ll, ll>>>& adj, ll s, ll e);
ll adj2tc(const vector<unordered_map<ll, ll>>& adj, ll e);
