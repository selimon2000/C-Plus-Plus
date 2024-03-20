// https://www.youtube.com/watch?v=noFeW2EagG8&list=PLk6CEY9XxSIC5KqCCuaIVcuuFaXfAVWy8&index=2&ab_channel=CppNuts


#include <iostream>


int findPosition(int N) {
    if(!N) return -1;
    int count = 0; // Count refers to element position, where first element posiiton is 0; not 1

    for (; N; N>>= 1) {
        count ++;

        if ((N & 1) == 1) {
            N>>= 1;
            break;
        }
    }

    if (!N) return count;
    else return -1;
}


int main() {
    std::cout << findPosition(1);
}