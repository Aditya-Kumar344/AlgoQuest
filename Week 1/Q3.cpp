#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
  int t, n, max = 0;
  cin >> t;
  for (int j = 0; j<t; j++)
  {
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i<n; i++) cin >> a[i];
    for (int i = 0; i<n; i++) cin >> b[i];
    vector<pair<int, int> > p;
    for (int i = 0; i<n; i++)
    {
      p.push_back(make_pair(a[i], b[i]));
    }
    sort(p.begin(), p.end());
    do
    {
      int x = 0;
      int beauty = 0;
      for (int i = 0; i<n; i++)
      {
        beauty += p[i].second * x;
        x += p[i].first;
      }
      if (max<beauty) max = beauty;
    } while (next_permutation(p.begin(), p.end())); // I think there may be some kind of sort method for optimal soln. that we can use which I was unable to figure out.
    cout << endl << max;
  }
}