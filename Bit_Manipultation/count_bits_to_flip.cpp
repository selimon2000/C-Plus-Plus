// How many bits need to be flipped to convert a to b
// https://www.youtube.com/watch?v=J6dv1vC7jUk&list=PLk6CEY9XxSIC5KqCCuaIVcuuFaXfAVWy8&index=6&ab_channel=CppNuts


#include <iostream>


int numOfBits(int a, int b) {
    int differences = a ^ b;

    int count = 0;
    for (; differences; differences>>=1) {
        if((differences & 1) == 1)
            count ++;
    }

    return count;
}


int main() {
    int a = 3;
    int b = 5;

    std::cout << numOfBits(a, b);
}