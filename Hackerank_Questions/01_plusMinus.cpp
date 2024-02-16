#include<bits/stdc++.h>
using namespace std;
 
 // Function to find the ratio of positive, negative, and zero elements in a vector
void plusMinus(vector<int> v)
{
    float p = 0, n = 0, z = 0;
    int len=v.size();
    
    for (int i = 0; i < len; i++)
    {
        if (v[i] > 0) {p++;}
        else if (v[i] < 0) {n++;}
        else{z++;}
    }
    printf("%f\n%f\n%f\n",p/(p+z+n), n/(p+z+n), z/(p+z+n));
}
 
int main()
{
    // Test Case 1:
    vector<int> v1 = { 2, -1, 5, 6, 0, -3 };
    plusMinus(v1);

    cout<<endl;

    // Test Case 2:
    vector<int> v2 = { 4, 0, -2, -9, -7, 1 };
    plusMinus(v2);
 }