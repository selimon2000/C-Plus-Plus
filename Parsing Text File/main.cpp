#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

typedef std::pair<int, std::string> sep_pair;

sep_pair separateNumberAndString(std::string input) {
    int number = 0;
    std::string str;

    std::istringstream iss(input);
    iss >> number;
    iss >> str;

    return std::make_pair(number, str);
}


int main() {

    std::ifstream file("coding_qual_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::map<int, std::string> my_map;

    std::string line;
    while (std::getline(file, line)) {
        // Separate string into number
        sep_pair my_pair = separateNumberAndString(line);
        my_map[my_pair.first] = my_pair.second;
    }

    int level = 0;
    int max = 0;
    for (auto pair : my_map) {
        
        if (level == max) {
            max ++;
            level = 0;
            std::cout << pair.second << " ";
        }
        level ++;
    }

    file.close(); // Close the file
    return 0;
}