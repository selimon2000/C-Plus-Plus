#include <bitset>
#include <iostream>

int main() {
    int a = -128;

    std::cout << std::bitset<8>(a);
}