// Create a function that accepts a double value as a parameter and
// Returns a bool value if the double is greater than zero and the
// square value instead of initial passed value.

#include <iostream>
#include <stdbool.h>
using namespace std;

bool squareOfCheckPositive(double &x)
{
  bool check = x > 0;
  x *= x;

  return check;
}

int main()
{
  double value = 0.1;
  cout <<"Is greater than 0: "<<squareOfCheckPositive(value) << endl;
  cout <<"value entered squared: "<<value << endl;
}