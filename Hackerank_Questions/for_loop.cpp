#include <iostream>
#include <cstdio>
using namespace std;

void my_function(int i, int j) {
    string numbers[9]{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    for (int n = i; n <= j; n++) {

        if (n >= 1 && n <= 9)
            std::cout << numbers[n-1];
        else if (n > 9 && n % 2 == 0)
            std::cout << "even";
        else
            std::cout << "odd";
        
        cout << endl;
    }
}

int main() {
    // Complete the code.
    // User Input
    int a, b;
    cin >> a >> b;
    my_function(a, b);
    
    return 0;
}