#include "arrays.h"
#include <random>    // Includes the random number generator
#include <chrono>    // Includes the system clock
#include <iterator>  // For using iterators in Lambda functions (ADVANCED)
#include <algorithm> //Can use algorithms on STL containers
using namespace std;

// function to populate array with random numbers
void populateWithRandomNumbers(double x[], unsigned int &array_size, unsigned int num_elements)
{

    // we select a seed for the random generator, so it is truly random (never the same seed)
    long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    // create a normal distribution with means zero and standard deviation 10
    std::normal_distribution<> distribution(0, 10.0);
    // generate the required amount of random numbers
    for (unsigned int i = array_size; i < array_size + num_elements; i++)
    {
        x[i] = distribution(generator);
    }
    // let's update the array size
    array_size += num_elements;
}

// 1) TASK: Implement function `assignArrayToVector`that assigns elements of array `x` to a vector named `vec`
void assignArrayToVector(double x[], unsigned int arraySize, std::vector<double> &myVec)
{
    for (int i = 0; i < arraySize; i++)
    {
        myVec[i] = x[i];
    }
}

// 2) TASK: Implement function `removeNumbersLargerThan` that accepts vector `myVec` and removes elements of `myVec` greater than a `limit`
void removeNumbersLargerThan(std::vector<double> &myVec, double limit)
{
    int vectorSize=myVec.size();
    for (int i = 0; i <vectorSize; i++)
    {
        if (myVec[i] > limit)
        {
            myVec.erase(myVec.begin()+i);
            i--;
            vectorSize--;
        }
    }
}

// 3) TASK: Implement function `computeMeanAndStdDev` that computes the mean and standard deviation of `myVec` and returns the `Stats` structure with these values.
Stats computeMeanAndStdDev(std::vector<double> myVec)
{

    Stats returnInfo;

    float sum = 0.0, mean, variance = 0.0, stdDeviation;
    int vectorSize=myVec.size();
    
    for (int i= 0; i < vectorSize; ++i)
        sum += myVec[i];
    mean = sum / vectorSize;

    for (int i= 0; i < vectorSize; ++i)
        variance += pow(myVec[i] - mean, 2);
    variance = variance / vectorSize;
    stdDeviation = sqrt(variance);

    returnInfo.mean = mean;
    returnInfo.std_dev = stdDeviation;

    return returnInfo;
}

// 4) TASK:  Implement function `returnVecWithNumbersSmallerThan` that returns a vector containing elements of `myVec` vector that are less than `limit`.
std::vector<double> returnVecWithNumbersSmallerThan(std::vector<double> myVec, double limit)
{
    int vectorSize=myVec.size();

    for (int i = 0; i < vectorSize; i++)
    {
        if (myVec[i] < limit)
        {
            myVec.erase(myVec.begin()+i);
            i--;
            vectorSize--;
        }
    }
    return myVec;
    // BONUS - Can you use a lambda function instead of looping?
}
