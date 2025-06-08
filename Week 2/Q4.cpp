#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

int main()
{
  string s;
  getline(cin, s);
  string p;
  getline(cin, p);
  cout << "[";
  int found = 0;
  for (int i = 0; i <= s.size() - p.size(); i++)
  {
    unordered_map<char, int> freq;
    for (int k = 0; k < p.size(); k++)
    {
      char c = p[k];
      freq[c]++;
    }
    for (int j = 0; j < p.size(); j++)
    {
      char c = s[i + j];
      freq[c]--;
    }
    int label = 1;
    for (int k = 0; k < p.size(); k++)
    {
      char c = p[k];
      if (freq[c] != 0)
      {
          label = 0;
          break;
      }
    }
    if (label == 1)
    {
      cout << i << ",";
      found = 1;
    }
  }
  if (found)
      cout << "\b";
  cout << "]";
  return 0;
}
