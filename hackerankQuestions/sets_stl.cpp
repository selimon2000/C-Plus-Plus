#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin >> N;
    
    set<int> my_set;
    
    for (int i = 0; i < N; i++) {
        int x, y; // y is the query
        cin >> y;
        cin >> x;
        
        if (y == 1)
            my_set.insert(x);
        else if(y == 2) {
            auto it = my_set.find(x);
            if (it != my_set.end())
                my_set.erase(it);
        }
        else if (y == 3) {
            auto it = my_set.find(x);
            if (it != my_set.end())
                cout << "Yes" << endl;
            
            else
                cout << "No" << endl;
        }
    }
    
    return 0;
}