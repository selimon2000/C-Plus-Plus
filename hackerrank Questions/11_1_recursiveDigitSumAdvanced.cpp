#include <iostream>
using namespace std;

int recfunction(long long no)
{
    long long sum=0;
    if (no<=9)
    {return no;}
    
    while(no>0)
    {
        sum+=no%10;
        no/=10;
    }
    return recfunction(sum);
}

int superDigit(string n, int k)
{
    long long no=0;
/* rather than converting with stoi, we can get each character in the string in its ASCII form, and minused with 48 as ASCII value for 0 is 48) */
    for (char x:n)
    {no+=x-48;}
    no*=k;
    
    return recfunction(no);
}

int main()
{
    cout<<superDigit("861568688536788", 100000);
}