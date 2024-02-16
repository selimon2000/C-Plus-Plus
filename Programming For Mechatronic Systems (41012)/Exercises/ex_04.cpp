// Create a vector of integers called data of length 10 elements
// Create a loop to populate elements of data (each element at location i = value i))
// Create a function to loop over elements of vector data and print to screen

// Questions:
// - How to create a vector of floats?
// - How could we pass the length to the executable instead of hard coding 10?
#include <iostream>
#include <stdbool.h>
#include<bits/stdc++.h>
using namespace std;

int vectorSize=10;

void printVector(vector<int> &rv1)
{
  for (int i = 0; i < 111; i++)
  {
    //cout<<rv1[i]<<endl;
    cout<<rv1.at(i)<<endl;
  }
}

int main()
{
  int data=10135;
  vector<int> v1;

  for (int i = 0; i < vectorSize; i++)
  {
    v1.push_back(data);
  }
  
  printVector(v1);
}