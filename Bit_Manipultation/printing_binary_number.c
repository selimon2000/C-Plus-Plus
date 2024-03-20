#include <stdio.h>


void printBinary(int num) {
    if(num > 1)
        printBinary(num >> 1);
    printf("%d ", num & 1);
}


int main() {
    unsigned int number = 11;
    printBinary(number);
}