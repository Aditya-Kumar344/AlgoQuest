#include <algorithm>

class Solution {
public:
  string getPermutation(int n, int k) {
    string s(n, ' ');
    for (int i = 0; i < n; i++) {
        s[i] = '1' + i;
    }
    k--;
    while (k--) {
        next_permutation(s.begin(), s.end());
    }
    return s;
  }
};
