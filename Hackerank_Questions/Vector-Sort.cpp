#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n;
    cin >> n;
    vector<int> my_vector (n, 0);
    for (int i = 0; i < n; i++)
        cin >> my_vector.at(i);
    
    sort(my_vector.begin(), my_vector.end());
    
    for (int i = 0; i < n; i++)
        cout << my_vector.at(i) << " ";
    
    return 0;
}
