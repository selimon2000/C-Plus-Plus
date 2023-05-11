#include "sample.h"
#include <iostream>
using namespace std;

int main () {


//  Create an object `sample` of `Sample` class
    Sample sample(31.45);
//  Display to standard output the value of parameter `value_` from the `sample` object.
    cout<<sample.readValue();
    return 0;
}