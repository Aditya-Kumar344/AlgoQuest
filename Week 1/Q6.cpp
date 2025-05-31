#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

int count(vector<int>& v, int i)
{
  int sum = 0;
    int len = 0;
    int max_len = 0;
    for (int j = i; j < v.size(); j++)
    {
      sum += v[j];
      len++;
      if (sum < 0) break;
      if (sum == 0) max_len = len;
    }

    return max_len;
}

int main()
{
  string s;
  cin >> s;
  map<char, int> mp;
  mp['('] = 1;
  mp[')'] = -1;
  vector<int> convert;
  for (int i = 0; i < s.length(); i++)
  {
      convert.push_back(mp[s[i]]);
  }
  int max_len = 0;
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i]=='(')
    {
      int len = count(convert, i);
      if (len>max_len) max_len = len;
    }
  }
  cout << max_len;
  return 0;
}