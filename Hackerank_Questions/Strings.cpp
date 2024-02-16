#include <iostream>
#include <string>
using namespace std;

int main() {
	// Complete the program
    string string_1, string_2;
    cin >> string_1 >> string_2;
    
    cout << string_1.length() << " " << string_2.length() << endl;
    cout << string_1 + string_2 << endl;
    
    swap(string_1[0], string_2[0]);
    cout << string_1 << " " << string_2 << endl;
    
    return 0;
}