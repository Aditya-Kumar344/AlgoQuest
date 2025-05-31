#include<iostream>
#include<vector>

using namespace std;

int find_subarray(vector<int> &a, int sum, int i, int n, int x)
{
  if (i==n) return (sum==x)?1:0;
  int include = find_subarray(a, sum+a[i], i+1, n, x);
  int exclude = find_subarray(a, sum, i+1, n, x);
  return include + exclude;
}

int main()
{
  int n, x;
  cin >> n >> x;
  vector<int> a(n);
  for (int i=0 ; i<n;i++)
  {
    cin >> a[i];
  }
  int count = find_subarray(a, 0, 0, n, x);
  cout << count;
}