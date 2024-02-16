#include "gtest/gtest.h"
#include <iostream> //Not needed usually, here just for debugging
#include <vector>
#include <algorithm>

//header files needed from our libraries
#include "../arrays.h"

using namespace std;

void printVec(vector<double> myVec){
    for (unsigned int i = 0; i<myVec.size(); i++) {
        std::cout << i << " " << myVec.at(i) << std::endl;
    }
    std::cout << "****************************************" << std::endl;
}


//1) TASK: Create a function that assigns elements of array x to a vector named `vec`
TEST (FunctionsTest, AssignArrayToVec) {

    double myArray[10]={-0.612444,3.03659,23.678,6.34389,15.0037,-6.98407,-9.78041,6.76262,6.69126,-3.38297};
    std::vector<double> myVec={-0.612444,3.03659,23.678,6.34389,15.0037,-6.98407,-9.78041,6.76262,6.69126,-3.38297};
    std::vector<double> returnVec;
    assignArrayToVector(myArray,10,returnVec);

    ASSERT_EQ(myVec.size(),10);
    bool result = std::equal(myVec.begin(), myVec.end(), returnVec.begin());
    ASSERT_TRUE(result);
}

//4) TASK: Create a function that retruns a vector containing elements of an initial vector that are less than a value
TEST (FunctionsTest, CopyVecElementsLessThan) {
    std::vector<double> myVec={-0.612444,3.03659,23.678,6.34389,15.0037,-6.98407,-9.78041,6.76262,6.69126,-3.38297};
    std::vector<double> newVec = returnVecWithNumbersSmallerThan(myVec, -3.38290);
    std::vector<double> returnVec={-6.98407,-9.78041,-3.38297};
    ASSERT_EQ(newVec.size(),3);
    bool result = std::equal(newVec.begin(), newVec.end(), returnVec.begin());
    ASSERT_TRUE(result);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
