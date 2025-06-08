#include<iostream>
#include<vector>
using namespace std;

int main()
{
  vector<int> v(301);
  char c;
  int x = 0;
  cin >> c;
  while (true)
  {
    cin >> v[x] >> c;
    x++;
    if (c==']') break;
  }
  for (int i = 0; i<x; i++)
  {
    for (int j = i+1; j<x; j++)
    {
      if (v[i]>v[j]) swap(v[i], v[j]);
    }
  }
  cout << "[";
  for (int i = 0; i<x-1; i++) cout << v[i] << ",";
  cout << v[x-1] << "]";
  return 0;
}