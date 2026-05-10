#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	void bubbleSort(vector<ll>& array) {
		ll n = ssize(array);
		for (ll i = n - 1; i > 0; --i) {
			for (ll j = 0; j < i; ++j) {
				if (array[j] > array[j + 1]) {
					swap(array[j], array[j + 1]);
				}
			}
		}
	}

	void mergeSort(span<ll> array) {
		if (array.size() <= 1)
			return;
		ll k = ssize(array) / 2;
		mergeSort(array.subspan(0, k));
		mergeSort(array.subspan(k));
		ranges::inplace_merge(array, array.begin() + k);
	}

	void countingSort(vector<ll>& array) {
		ll c = array.empty() ? 0 : ranges::max(array);
		vector<ll> count(c + 1);
		for (ll i : array)
			++count[i];
		auto it = array.begin();
		for (ll i = 0; i <= c; ++i) {
			for (ll j = 0; j < count[i]; ++j) {
				*it++ = i;
			}
		}
	}

	void test(auto f) {
		vector<ll> array;
		f(array);
		EXPECT_EQ(array, vector<ll>{});
		array = { 1,3,8,2,9,2,5,6 };
		f(array);
		EXPECT_EQ(array, (vector<ll>{ 1,2,2,3,5,6,8,9 }));
		array = { 1,3,6,2,8,2,5,9 };
		f(array);
		EXPECT_EQ(array, (vector<ll>{ 1,2,2,3,5,6,8,9 }));
		array = { 1,3,6,9,9,3,5,9 };
		f(array);
		EXPECT_EQ(array, (vector<ll>{ 1,3,3,5,6,9,9,9 }));
	}
}

TEST(C031SortingTheory, bubbleSort) {
	test(bubbleSort);
}

TEST(C031SortingTheory, mergeSort) {
	test(mergeSort);
}

TEST(C031SortingTheory, countingSort) {
	test(countingSort);
}
