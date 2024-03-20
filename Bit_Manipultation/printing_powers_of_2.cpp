#include <iostream>


int main() {

    // Printing from lowest to highest int
    // for (int num = 1, i = 0; i < 31; i++)
    //     std::cout << (num << i) << std::endl;

    // Printing from highest to lowest int
    for (int num = 1, i = 30; i >= 0; i--)
        std::cout << i << '\t' << (num << i) << std::endl;
}