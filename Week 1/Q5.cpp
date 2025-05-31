#include<iostream>
#include<string>
using namespace std;

int isValid(string s)
{
  int i;
  while(1)
  {
    int old_len = s.size();
    while((i = s.find("()"))!=string::npos) s.erase(i, 2);
    while((i = s.find("{}"))!=string::npos) s.erase(i, 2);
    while((i = s.find("[]"))!=string::npos) s.erase(i, 2);
    int new_len = s.size();
    if (old_len == new_len) break;
  }
  if (s.empty()) return 1;
  else return 0;
}

int main()
{
  string s;
  cin >> s;
  if (isValid(s)) cout << "true";
  else cout << "False";
}