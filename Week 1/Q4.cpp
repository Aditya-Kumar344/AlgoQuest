#include<iostream>
#include<vector>
using namespace std;

int main()
{
  int t;
  cin >> t;
  for (int k = 0; k<t; k++)
  {
    int n, flag = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i<n; i++) cin >> a[i];
    vector<pair<int, int> > s;
    for (int i = 0; i<n; i++) s.push_back(make_pair(a[i], 0));
    for (int i = 0; i<n-1; i++)
    {
      for (int j = 0; j<n-i-1; j++)
      {
        if (s[j].first > s[j + 1].first)
        {
          swap(s[j], s[j+1]);
          s[i].second++;
          s[j+1].second++;
        }
      }
    }
    for (int i = 0; i<n; i++)
    {
      if (s[i].second % 2 == 1)
      {
        flag = 1;
        break;
      } 
    }
    if (flag == 0) cout << endl << "YES";
    else cout << endl << "NO";
  }
}