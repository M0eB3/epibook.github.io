// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int SearchFirstOfK(const vector<int>& A, int k) {
  int left = 0, right = A.size() - 1, result = -1;
  // [left : right] is the candidate set.
  while (left <= right) {
    int mid = left + ((right - left) / 2);
    if (A[mid] > k) {
      right = mid - 1;
    } else if (A[mid] == k) {
      result = mid;
      right = mid - 1;  // Nothing to the right of mid can be solution.
    } else {  // A[mid] < k.
      left = mid + 1;
    }
  }
  return result;
}
// @exclude

int SearchFirstOfKAlternative(const vector<int>& A, int k) {
  auto result = lower_bound(A.begin(), A.end(), k);
  if (*result == k) {
    return distance(A.begin(), result);
  }
  return -1;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 100000);
      n = dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> k_dis(0, n - 1);
    int k = k_dis(gen);
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(0, n - 1);
      A.emplace_back(dis(gen));
    }
    sort(A.begin(), A.end());
    int ans = SearchFirstOfK(A, k);
    assert(SearchFirstOfKAlternative(A, k) == ans);
    cout << "k = " << k << " locates at " << ans << endl;
    if (ans != -1) {
      cout << "A[k] = " << A[ans] << endl;
    }
    auto it = find(A.cbegin(), A.cend(), k);
    assert((it == A.cend() && ans == -1) || (distance(A.cbegin(), it) == ans));
  }
  return 0;
}
