#include<iostream>
#include<vector>
using namespace std;

int main()
{
  vector<int> v(10001);
  char c;
  int x = 0;
  cin >> c;
  while (true)
  {
    cin >> v[x++] >> c;
    if (c==']') break;
  }
  int b;
  cin >> b;
  int count = 0, start = 0, sum = 0;
  for (int end = 0; end<x; end++)
  {
    sum += v[end];
    while (sum >= b && start <= end) sum -= v[start++];
    count += end - start + 1;
  }
  cout << count;
  return 0;
}