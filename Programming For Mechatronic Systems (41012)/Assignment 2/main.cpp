#include "pfms_types.h"
#include <iostream>
#include "logger.h"
#include "mission.h"
#include <string.h>

int main(int argc, char *argv[])
{

    // Default location of files containing sequence of points and objective
    std::string ackerman_filename = "../data/ACKERMAN.TXT";
    std::string quadcopter_filename = "../data/QUADCOPTER.TXT";
    mission::Objective objective = mission::Objective::BASIC;

    // Will default to the settings unless specified with ovvride as arguments
    // Example ./assignment2 --advanced $HOME/data/ACKERMAN.TXT $HOME/data/QUADCOPTER.TXT
    // This woudl assume your files are in home directory in data subfolder
    // You do need the -- (two "-") to enable ADVANCED MODE
    if (argc < 4)
    {
        std::cout << "To override Run with 3 arguments: " << std::endl;
        std::cout << argv[0] << " MODE (--advanced) location_of_ACKERMAN.txt location_of_QUADCOPTER.txt" << std::endl;
    }
    else
    {
        if (strcmp(argv[1], "-advanced"))
        {
            std::cout << "Advanced Mode Activated" << std::endl;
            objective = mission::Objective::ADVANCED;
        }
        ackerman_filename = argv[2];
        quadcopter_filename = argv[3];
    }

    std::vector<pfms::geometry_msgs::Point> ackermanPoints;
    std::vector<pfms::geometry_msgs::Point> quadcopterPoints;

    // If the files can not be opened we will terminate
    if (!logger::loadPoints(ackerman_filename, ackermanPoints))
    {
        std::cout << "Could not load points from file:" << ackerman_filename << std::endl;
        return 0;
    }

    if (!logger::loadPoints(quadcopter_filename, quadcopterPoints))
    {
        std::cout << "Could not load points from file:" << quadcopter_filename << std::endl;
        return 0;
    }

    std::cout << "Size of Ackerman goals:" << ackermanPoints.size() << std::endl;
    std::cout << "Size of Quadcopter goals:" << quadcopterPoints.size() << std::endl;

    return 0;
}

// #include <iostream>
// using namespace std;
// #include <vector>

// void print_adjacency_list(vector<vector<pair<int, double>>> graph)
// {
//     if (graph.empty())     // If stack is empty then return
//         return;

//     unsigned int nodeNum = 0;
//     for (auto edges : graph)
//     {
//         cout << "[" << nodeNum++ << "] ";
//         for (auto nodes : edges)
//         {std::cout << nodes.first << ":" << nodes.second << " ";}
//         std::cout << std::endl;
//     }
// }

// std::vector<pfms::geometry_msgs::Point> TSPAdvancedMode(std::vector<pfms::geometry_msgs::Point> originalGoals)
// {
//     vector<vector<pair<int, double>>> graph;
//     vector<pair<int, double>> initialGraphRowVector;
//     pair<int, double> pushPair;
//     pushPair.second = 0;
//     int n = originalGoals.size();
//     double distance;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             pushPair.first = i;
//             initialGraphRowVector.push_back(pushPair);
//         }
//         graph.push_back(initialGraphRowVector);
//     }
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {graph.at(i).at(j).second = std::hypot(originalGoals.at(i).x - originalGoals.at(i).y, originalGoals.at(j).x - originalGoals.at(j).y);}
//     }

//     print_adjacency_list(graph);
//     std::vector<pfms::geometry_msgs::Point> order;
//     return order;
// }

// int main()
// {
//     std::vector<pfms::geometry_msgs::Point> goals;
//     goals.push_back({ 10, -2});
//     goals.push_back({ 10,  6});
//     TSPAdvancedMode(goals);
// }