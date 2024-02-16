// Create a structure called Sensor than contains:
// - A variable for the number of samples num_samples
// - An array of samples double data[]
// - Create a variable called sensor of type Sensor

// Populate data of sensor with 5 elements, each data[i] =i. How to code end of loop?
// Create a function that prints samples
// Can you initialise a sensor of two elements in one line of code?

#include <iostream>
#include <stdbool.h>
using namespace std;

static const int array_size = 5;

struct Sensor
{
  double num_samples, data[array_size];
};

int main()
{
  int value = 11;
  Sensor sensor;
  sensor.num_samples = array_size;

  for (int i = 0; i < sensor.num_samples; i++)
  {
    sensor.data[i] = value;
  }

  // print array:
  cout << "Printing array:" << endl;
  for (int i = 0; i < sensor.num_samples; i++)
  {
    cout << sensor.data[i] << endl;
  }
}