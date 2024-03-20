#include <iostream>


bool isPowerOf2(int num) {
    if (num <=0)
        return false;
    
    if ((num & (num - 1)) == 0)
        return true;

    return false;
}


int main() {
    int num = 32;
    std::cout << isPowerOf2(num) << std::endl;
}