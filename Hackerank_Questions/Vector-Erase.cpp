#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin >> N;
    
    vector<int> my_vector(N, 0);
    for (int i = 0; i < N; i++)
        cin >> my_vector.at(i);
    
    int pos;
    cin >> pos;
    my_vector.erase(my_vector.begin() + pos - 1);
    
    int pos_a, pos_b;
    cin >> pos_a >> pos_b;
    my_vector.erase(my_vector.begin() + pos_a - 1, my_vector.begin() + pos_b - 1);
    
    cout << my_vector.size() << endl;
    for (auto number : my_vector)
        cout << number << " ";
    
    return 0;
}
