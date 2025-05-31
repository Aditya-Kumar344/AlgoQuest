#include<iostream>
#include<vector>

using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i<n; i++)
  {
    cin >> a[i];
  }
  for (int i = 0; i<n; i++)
  {
    for (int j = i; j<n; j++)
    {
      if (a[i]>a[j])
      {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
  int count = 1, max = 1;
  for (int i = 0; i<n-1; i++)
  {
    if (a[i]==a[i+1]) count+=1;
    else{
      if (max<count) max = count;
      count = 1;
    }
  }
  if (max < count) max = count;
  cout << max;
}