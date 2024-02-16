#include "analysis.h"
#include <iostream> // Only here for showing the code is working
#include <string>
using namespace std;

namespace analysis
{

    //! @todo
    //! TASK 4 - Refer to README.md and the Header file for full description
    unsigned int countCharacters(std::string sentence)
    {
        // unsigned int count = 0;
        unsigned int count = sentence.size();

        return count;
    }

    // //! @todo
    // //! TASK 5 - Refer to README.md and the Header file for full description
    // int getNumber(std::string sentence)
    // {
    //     // unsigned int num = 0;
    //     // return num;

    //     std::vector<int> intCollector;
    //     int number;

    //     for (int i = 0; i < sentence.size(); i++)
    //     {
    //         if (isdigit(sentence[i]) == true)
    //         {
    //             while (isdigit(sentence[i]) == true)
    //             {
    //                 intCollector.push_back(sentence[i]);
    //                 i++;
    //             }

    //             for (int i = intCollector.size(); i >= 0; i--)
    //             {

    //             }
    //             return
    //         }
    //     }
    // }

    //! @todo
    //! TASK 5 - Refer to README.md and the Header file for full description
    int getNumber(std::string sentence)
    {
        std::string newString;

        for (int i = 0; i < sentence.size(); i++)
        {
            if (isdigit(sentence[i]) == true)
            {
                while (isdigit(sentence[i]) == true)
                {
                    newString.push_back(sentence[i]);
                    i++;
                }
                return stoi(newString);
            }
        }
        return 0;
    }

}