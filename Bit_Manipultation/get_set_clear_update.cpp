#include <iostream>


bool getBit (int num, int i) {
    return ((num & (1<<0)) != 0);
}

// Clearing a certain bit - making it zero
void clearBit(int& num, int pos) {
     num = num & ~(1 << pos);
}

void clearBitsMsbThroughI(int& num, int i) {
    int mask = (1 << i) - 1;
    num &= mask;
}

void clearBitsIThrough0(int& num, int i) {
    // First we take a sequence of all 1s (which is -1)
    // Then we shift it such that there is 0 on the places to be terminated 
    int mask = (-1 << (i + 1));
    num &= mask;
}

// With if statement
void updateBitOld(int& num, int pos, int val) {
    if (val == 0)
        num = num & ~(1 << pos);
    else 
        num = num | (1 << pos);
}
void updateBit(int& num, int i, bool bitIs1) {
    int value = (bitIs1) ? 1 : 0;
    int mask = ~(1 << i);
    num = (num & mask) | (value << i);
}

int main() {
    int num = 310;

    // std::cout << getBit(num, 0) << std::endl;

    // setBit(num, 0, 1);
    // std::cout << num << std::endl;

    // clearBitsIThrough0(num, 3);
    // std::cout << num << std::endl;

    // updateBitOld(num, 0, 1);
    updateBit(num, 0, 0);
    std::cout << (num);
}