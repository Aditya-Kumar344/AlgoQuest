#include<iostream>
#include<vector>
using namespace std;

int main()
{
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i<n; i++) cin >> v[i];
  int max_len = 0, start = 0, sum = 0;
  for (int end = 0; end < n; end++) 
  {
    sum += v[end];
    while (sum > k && start <= end)
    {
      sum -= v[start];
      start++;
    }
    if (sum == k)
    {
      max_len = max(max_len, end - start + 1);
    }
  }
  cout << max_len;
  return 0;
}