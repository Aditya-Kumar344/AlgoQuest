#include<iostream>
#include<vector>
using namespace std;

int main()
{
  vector<int> v(40001);
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
  vector<int> freq(x, 0);
  for (int i = 0; i<x; i++) freq[i] = 0;
  int count = 0, distinct = 0, start = 0;
  for (int end = 0; end<x; end++)
  {
    if (freq[v[end]] == 0)  distinct++;
    freq[v[end]]++;
    while (distinct > b)
    {
      freq[v[start]]--;
      if (freq[v[start]] == 0) distinct--;
      start++;
    }
    if (distinct==b)
    {
      int temp = start;
      while (freq[v[temp]]>1)
      {
        freq[v[temp]]--;
        temp++;
      }
      count+=temp-start+1;
      for (int i = start; i < temp; i++) freq[v[i]]++;
    }
  }
  cout << count;
  return 0;
}