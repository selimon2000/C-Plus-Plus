#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {
    // Complete the code.
    
    std::cout << std::fixed;
    
    int input_1;
    long input_2;
    char input_3;
    float input_4;
    double input_5;
    
    cin >> input_1  >> input_2  >> input_3  >> input_4 >> input_5;
    cout << input_1 << endl << input_2 << endl << input_3 << endl << setprecision(3) << input_4 << endl << setprecision(9) << input_5;
    
    return 0;
}