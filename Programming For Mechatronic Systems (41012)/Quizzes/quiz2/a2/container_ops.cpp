#include "container_ops.h"
#include <random>    // Includes the random number generator
#include <chrono>    // Includes the system clock
#include <iterator>  // For using iterators in Lambda functions (ADVANCED)
#include <algorithm> //Can use algorithms on STL containers

void populateContainer(std::deque<double> &container, unsigned int num_values, double element)
{
    // std::deque<double> returnDeque;

    // for (int i = 0; i < num_values; i++)
    // {
    //     returnDeque.push_back(element);
    // }
    // for (int i = 0; i < container.size(); i++)
    // {
    //     returnDeque.push_back(container.at(i));
    // }

    for (int i = 0; i < num_values; i++)
    {
        container.insert(container.begin(), element);
    }
}

// void bubbleSortContainer(std::deque<double> &container)
// {
//     int size = container.size();

//     // loop to access each array element
//     for (int step = 0; step < size; ++step)
//     {
//         // loop to compare array elements
//         for (int i = 0; i < size - step; ++i)
//         {
//             // compare two adjacent elements
//             // change > to < to sort in descending order
//             if (container.at(i) > container.at(i + 1))
//             {
//                 // swapping elements if elements are not in the intended order
//                 int temp = container.at(i);
//                 container.at(i) = container.at(i + 1);
//                 container.at(i + 1) = temp;
//             }
//         }
//     }
// }2


void bubbleSortContainer(std::deque<double> &container)
{
    bool isSwapped{false};

    do
    {
        isSwapped = true;

        for (size_t i = 0; i < container.size()-1; i++)
        {
            if (container.at(i)>container.at(i+1))
            {
                std::swap(container.at(i), container.at(i+1));
                isSwapped=false;
            }
        }
    } 
    while (!isSwapped);
}