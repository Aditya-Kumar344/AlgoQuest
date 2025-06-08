#include<iostream>
#include<vector>
using namespace std;

int main()
{
  vector<int> v(3001);
  vector<vector<int> > n;
  int len = 0;
  char c;
  cin >> c;
  while (true)
  {
    cin >> v[len];
    cin >> c;
    len++;
    if (c==']')
    {
      break;
    }
  }
  for (int i = 0; i<len; i++)
  {
    for (int j = i+1; j<len; j++)
    {
      if (v[i]>v[j])
      {
        swap(v[i], v[j]);
      }
    }
  }
  for (int i = 0; i<len; i++)
  {
    if (i > 0 && v[i] == v[i - 1]) continue;
    int target = -v[i];
    int j = i+1;
    int k = len-1;
    while (j<k)
    {
      if (v[j]+v[k]==target)
      {
        vector<int> triplet(3);
        triplet[0] = v[i];
        triplet[1] = v[j];
        triplet[2] = v[k];
        n.push_back(triplet);
        j++;
        k--;
        while (j < k && v[j] == v[j - 1]) j++;
        while (j < k && v[k] == v[k + 1]) k--;
      }
      else if (v[j]+v[k] < target) j++;
      else k--;
    }
  }
  cout << "[";
  for (int i = 0; i<n.size(); i++)
  {
    cout << "[" << n[i][0] << "," << n[i][1] << "," << n[i][2] << "]";
    if (i<n.size()-1) cout << ",";
  }
  cout << "]";
  return 0;
}