#include<bits/stdc++.h>
using namespace std;
//  Given five positive integers, find the minimum and maximum values that can be calculated by summing exactly four
//  of the five integers. Then print the respective minimum and maximum values as a single line of two space-separated 
//  long integers.

void miniMaxSum(vector<int> arr) {
int len=arr.size();
int bigPos=0, smallPos=0;
long int big=arr[0], small=arr[0], minSum=0, maxSum=0;

for(int i=1;i<len;i++){
    //find biggest number
    if (arr[i]>big){
        big=arr[i];
        bigPos=i;
        }
    //find smallest number
    if (arr[i]<small){
        small=arr[i];
        smallPos=i;
        }
    }
    //find sum of min
    for(int i=0;i<len;i++){
        if (i!=bigPos)
        {minSum+=arr[i];}
    }
    //find sum of max
    for(int i=0;i<len;i++){
        if (i!=smallPos)
        {maxSum+=arr[i];}
    }
    
    cout<<minSum<<" "<<maxSum<<endl;
}
 
int main()
{
    // Test Case 1:
    vector<int> v1 = { 1, 3, 5, 7, 9};
    miniMaxSum(v1);

    cout<<endl;

    // Test Case 2:
    vector<int> v2 = { 7, 69, 2, 221, 8974 };
    miniMaxSum(v2);
 }