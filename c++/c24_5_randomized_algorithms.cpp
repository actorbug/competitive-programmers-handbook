#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c23_1_operations.h"

namespace {
    ll partition(vector<ll>& a, ll left, ll right, ll pivotIndex) {
        ll pivotValue = a[pivotIndex];
        swap(a[pivotIndex], a[right]);
        ll storeIndex = left;
        for (ll i = left; i < right; ++i) {
            if (a[i] <= pivotValue) {
                swap(a[storeIndex], a[i]);
                ++storeIndex;
            }
        }
        swap(a[right], a[storeIndex]);
        return storeIndex;
    }

    ll order_statistics(vector<ll> a, ll k) {
        mt19937 engine;
        ll left = 0, right = ssize(a) - 1;
        while (true) {
            ll pivotIndex = uniform_int_distribution<ll>(left, right)(engine);
            ll pivotNewIndex = partition(a, left, right, pivotIndex);
            if (k == pivotNewIndex)
                return a[k];
            else if (k < pivotNewIndex)
                right = pivotNewIndex - 1;
            else
                left = pivotNewIndex + 1;
        }
    }

    bool verify(const M& a, const M& b, const M& c) {
        mt19937 engine;
        vector<double> v(c.v[0].size());
        for (double& i : v)
            i = uniform_real_distribution<>(0, 1)(engine);
        M x = M({ move(v) }).transpose();
        return a * (b * x) == c * x;
    }

    unordered_map<ll, bool> coloring(const vector<pair<ll, ll>>& edges) {
        mt19937 engine;
        unordered_map<ll, bool> d;
        for (auto [i, j] : edges) {
            d[i] = false;
            d[j] = false;
        }
        while (true) {
            for (auto& [k, v] : d)
                v = uniform_int_distribution<>(0, 1)(engine) > 0;
            ll c = 0;
            for (auto [i, j] : edges)
                c += d[i] != d[j];
            if (c >= (ssize(edges) + 1) / 2)
                return d;
        }
    }
}

TEST(C245RandomizedAlgorithms, orderStatistics) {
    EXPECT_EQ(order_statistics({8,4,3,7,6,5,2,1}, 3), 4);
}

TEST(C245RandomizedAlgorithms, verify) {
    EXPECT_FALSE(verify(M({{1,0},{0,1}}), M({{6,8},{1,3}}), M({{8,7},{3,2}})));
}

TEST(C245RandomizedAlgorithms, coloring) {
    EXPECT_EQ(coloring({}), (unordered_map<ll, bool>{}));
    vector<pair<ll, ll>> edges = {{0,1},{0,2},{0,3},{1,3},{1,4},{2,3},{3,4}};
    auto d = coloring(edges);
    ll c = 0;
    for (auto [i, j] : edges)
        c += d[i] != d[j];
    EXPECT_GE(c, 4);
}
