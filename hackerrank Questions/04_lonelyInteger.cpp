/*Given an array of integers, where all elements but one occur twice, find the unique element.
Example: a={1,2,3,4,3,2,1}
The unique element is '4'.*/

#include<bits/stdc++.h>
using namespace std;

int lonelyinteger(vector<int> a)
{  
    sort(a.begin(), a.end());
    int len=a.size();
    int answer=0;
    
    for (int i=0; i<len; i++)
    {
        if((a[i]!=a[i+1])&&(a[i]!=a[i-1]))
        {
        answer= a[i];
        exit;
        }
    }
    return answer;
}

int main()
{
    // Test Case 1:
    vector<int> v1 = { 1, 3, 5, 7, 9};
    cout<<lonelyinteger(v1)<<endl;

    // Test Case 2:
    vector<int> v2 = { 7, 69, 2, 221, 8974 };
    cout<<lonelyinteger(v2)<<endl;
 }