#include <iostream>

using namespace std;

// int addInt(int a, int b) {
//   return a + b;
// }

// int addFloat(int a, int b) {
//   return a + b;
// }

template <typename T>
T add(T a, T b)
{
  return a + b;
}

int main()
{
  // cout << addInt(5, 7) << endl;
  cout << add(5.7, 4.7) << endl;
  cout << add(5, 8) << endl;
  return 0;
}