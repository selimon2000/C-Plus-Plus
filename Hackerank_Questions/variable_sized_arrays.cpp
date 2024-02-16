#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, q;
    cin >> n >> q;
    
    vector<vector<int>> double_vector(n, vector<int>(0));
    
    for (int i = 0; i < n; i++) {
        int array_size;
        cin >> array_size;
        for (int j = 0; j < array_size; j++) {
            int scanned_input;
            cin >> scanned_input;
            double_vector.at(i).push_back(scanned_input);
        }
    }
    
    for (int x = 0; x < q; x++) {
        int sub_array, index;
        cin >> sub_array >> index;
        cout << double_vector.at(sub_array).at(index) << endl;
    }
    
    return 0;
}