#include <iostream>
using namespace std;

int main(){

  int a;
  int b = 12;
  a = 0; // there was a missing semicolon here causing the build to fail

  cout << "a = " << a << endl;
  cout << a+b << '\n' << "a-b = " << a-b << endl;

  return 0;
}
