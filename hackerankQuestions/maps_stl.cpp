#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    map<string, int> student_map;
    
    int Q; // Number of Queries
    cin >> Q;
   
    for (int i = 0; i < Q; i++) {
        int query_type;
        cin >> query_type;
        
        // Add marks to student whose
        if (query_type == 1) {
            string name;
            cin >> name;
            int mark;
            cin >> mark;
            
            auto it = student_map.find(name);
            if (it != student_map.end())
                student_map[name] += mark;
            else
                student_map[name] = mark;
        }
        else if (query_type > 1 && query_type < 4) {
            string name;
            cin >> name;
            // Erase the marks of the student
            if (query_type == 2)
                student_map.erase(name);
            // Print the marks of the student
            else {
                auto it = student_map.find(name);
                if (it == student_map.end())
                    cout << 0 << endl;
                else
                    cout << student_map.at(name) << endl;
            }
        }
    }
    
    return 0;
}



