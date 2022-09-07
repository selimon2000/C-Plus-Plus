#include <iostream>
using namespace std;

void addDigitsFunction(long long* x)
{
    int y = 0;
    while (*x > 0)
    {
        y += *x % 10;
        *x /= 10;
    }
    *x = y;
}

int superDigit(string n, int k)
{
    long long x = stoi(n), y=0;
    addDigitsFunction(&x);
    x*=k;

    do
    {
    addDigitsFunction(&x);
    } while (x > 9);

    return x;
}

int main()
{
    cout<<superDigit("9875", 4);
}