#include "sample.h"

// This is the implementation file (cpp) file, where functions declared in (h) need to
// be implemented

//1) TASK:

Sample::Sample (double value)
{
    value_=value;
}


//2) TASK: Implement ALL the methods of the Sample class in the [sample.cpp](./b/sample.cpp) file based on the definition provided in [sample.h](./b/sample.h).
// Your code will not compile until the functions are implemented.

void Sample:: setValue (double value)
{
    value_=value;
}

double Sample:: readValue ()
{
    return value_;
}
