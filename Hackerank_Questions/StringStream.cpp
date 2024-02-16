#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
	// Complete this function
    vector<int> return_vector;

    stringstream ss(str);
    int input_number;
    char comma;
    
    while(ss >> input_number) {
        ss >> comma;
        return_vector.push_back(input_number);
    }
    
    return return_vector;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}