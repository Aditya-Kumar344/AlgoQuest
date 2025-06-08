#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
  string s;
  getline(cin, s);
  vector<int> freq(256, 0);
  int max_len = 0, start = 0;
  for (int end = 0; end < s.size();end++)
  {
    freq[(int)s[end]]++;
    while (freq[(int)s[end]] > 1)
    {
      freq[(int)s[start]]--;
      start++;
    }
    max_len = max(max_len, end - start + 1);
  }
  cout << max_len;
  return 0;
}