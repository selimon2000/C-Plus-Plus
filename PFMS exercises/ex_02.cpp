// Create an additional function that accepts a double value as a parameter and
// Returns the following:
// - bool indicating if value is greater than zero
// - square of value instead of the initially passed value
// - passed value incremented by one

#include <iostream>
#include <stdbool.h>
using namespace std;

bool squareOfCheckPositive(double &x, double &rIncrement)
{
  bool check = x > 0;
  rIncrement=x+1;
  x *= x;

  return check;
}

int main()
{
  double increment, value;

  cout<<"enter a value: ";
  cin>>value;
  cout <<"\nIs greater than 0: "<<squareOfCheckPositive(value, increment) << endl;
  cout <<"value entered squared: "<<value << endl;
  cout <<"value entered incremented: "<<increment << endl;
}