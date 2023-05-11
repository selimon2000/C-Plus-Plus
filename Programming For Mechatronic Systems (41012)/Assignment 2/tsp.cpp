#include "tsp.h"
#define _USE_MATH_DEFINES

/*!
 *  \brief     TSP Class Implementation File
 *  \details
 *  Calculates The TSP (Travelling Salesman Problem) so that both the ackerman (audi) and quadcopter travel with the most optimised path.
 *  The calculations use brute force, where it searches all possible permuations, and uses the one which costs less, whilst being possible for both platforms.
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning
 */

// Default constructor should set all sensor attributes to a default value
TSP::TSP(std::vector<ControllerInterface *> controllers)
{
    controllers_ = controllers;
}

std::vector<pfms::geometry_msgs::Point> TSP::advancedMode(std::vector<pfms::geometry_msgs::Point> originalGoals, pfms::nav_msgs::Odometry origin)
{
    double savedYaw = 0;

    originaGoals_ = originalGoals;

    AdjacencyList graph;
    pair<int, double> pushPair;
    pushPair.second = 0;

    pfms::geometry_msgs::Point origin_;
    origin_.x = origin.position.x;
    origin_.y = origin.position.y;
    originaGoals_.insert(originaGoals_.begin(), origin_);

    int n = originaGoals_.size();
    double distance;

    for (int i = 0; i < n; i++)
    {
        vector<pair<int, double>> initialGraphRowVector;
        for (int j = 0; j < n; j++)
        {
            pushPair.first = j;
            if (j != i)
            {
                pfms::nav_msgs::Odometry odo_current___;
                pfms::geometry_msgs::Point goal;
                pfms::nav_msgs::Odometry estimatePose;
                double time;
                double distance;
                estimatePose.yaw = 0;

                for (int x = 0; x < controllers_.size(); x++)
                {
                    odo_current___.position.x = originaGoals_.at(i).x;
                    odo_current___.position.y = originaGoals_.at(i).y;
                    odo_current___.yaw = estimatePose.yaw;

                    goal = originaGoals_.at(j);

                    controllers_.at(x)->checkOriginToDestination(odo_current___, goal, distance, time, estimatePose);
                    savedYaw = estimatePose.yaw;

                    if (isnan(distance))
                    {
                        distance = 999;
                    }

                    pushPair.second = distance;
                    initialGraphRowVector.push_back(pushPair);
                }
            }
        }
        graph.push_back(initialGraphRowVector);
    }

    cout << "Printing Graph" << endl;
    printAdjacencyList(graph);

    cout << "Brute Force Permutations:" << endl;
    vector<int> path = bruteForceTSP(graph, 0);
    cout << "Printing Path: " << endl;
    printPath(graph, path);

    std::vector<pfms::geometry_msgs::Point> returnVector;
    for (int i = 1; i < n; i++)
    {
        returnVector.push_back(originaGoals_.at(path.at(i)));
    }
    return returnVector;
}

std::vector<pfms::geometry_msgs::Point> TSP::advancedModeCarNew(vector<pfms::geometry_msgs::Point> originalGoals, pfms::nav_msgs::Odometry origin)
{
    vector<int> nodes;
    for (unsigned int i = 0; i < originalGoals.size() + 1; i++)
    {
        nodes.push_back(i);
    }
    vector<vector<int>> possiblePermutationPaths;
    // This while loop creates all possible permutations of the nodes
    // We can use this while loop to create an order of ID's visited
    // Let's look for te total path to visit nodes in current node order
    do
    {
        std::vector<int> vec;

        for (auto node : nodes)
        {
            vec.push_back(node);
        }

        possiblePermutationPaths.push_back(vec); // encode all the path that start from 0

    } while ((std::next_permutation(nodes.begin(), nodes.end())) & (nodes.at(0) == 0));

    double minimum = 10000;
    vector<int> shortestPath;

    for (int i = 0; i < possiblePermutationPaths.size(); i++)
    {
        pfms::nav_msgs::Odometry odo_current = origin;
        pfms::nav_msgs::Odometry estimatePose;
        double time;
        double distance;
        double totalDistance = 0;
        bool possible = true;

        for (int j = 0; j < possiblePermutationPaths.at(i).size() - 1; j++)
        {
            for (int x = 0; x < controllers_.size(); x++)
            {

                if (controllers_.at(x)->checkOriginToDestination(odo_current, originalGoals.at(possiblePermutationPaths.at(i).at(j + 1) - 1), distance, time, estimatePose))
                {
                    odo_current = estimatePose;
                    totalDistance += distance;
                }
                else
                {
                    possible = false;
                }
            }
        }
        if (totalDistance < minimum && possible)
        {
            minimum = totalDistance;
            shortestPath = possiblePermutationPaths.at(i);
        }
    }

    std::vector<pfms::geometry_msgs::Point> returnVec;
    cout << "L " << shortestPath.size() << endl;
    for (int i = 1; i < shortestPath.size(); i++)
    {
        returnVec.push_back(originalGoals.at(shortestPath.at(i) - 1));
        cout<<"_"<<shortestPath.at(i);
    }
    return returnVec;
}


vector<int> getOrder(vector<pfms::geometry_msgs::Point> original, vector<pfms::geometry_msgs::Point> newOrder)
{
    vector<int> returnVector;

    for (int i = 0; i < original.size(); i++)
    {
        for (int j = 0; j < original.size(); i++)
        {
            if (original.at(i).x == newOrder.at(i).x && original.at(i).y == newOrder.at(i).y)
            {
                returnVector.push_back(j);
            }
        }
    }
    return returnVector;
}

void TSP::printPath(AdjacencyList graph, vector<int> path)
{
    // If graph is empty then return
    if (graph.empty())
    {
        return;
    }
    // If path is empty then return
    if (path.empty())
    {
        return;
    }

    for (unsigned int i = 0; i < path.size() - 1; i++)
    {
        unsigned int node1 = path.at(i);
        unsigned int node2 = path.at(i + 1);
        std::cout << "[" << node1 << "] to ";
        for (unsigned int j = 0; j < graph.at(node1).size(); j++)
        {
            if (graph.at(node1).at(j).first == node2)
            {
                cout << "[" << graph.at(node1).at(j).first << "] = " << graph.at(node1).at(j).second << endl;
                break;
            }
        }
    }
}

void TSP::printAdjacencyList(AdjacencyList graph)
{
    if (graph.empty()) // If stack is empty then return
    {
        return;
    }

    unsigned int nodeNum = 0;
    for (auto edges : graph)
    {
        cout << "[" << nodeNum++ << "] ";
        for (auto nodes : edges)
        {
            std::cout << nodes.first << ":" << nodes.second << " ";
        }
        std::cout << std::endl;
    }
}

vector<int> TSP::bruteForceTSP(AdjacencyList graph, int start)
{
    int n = graph.size();
    vector<int> returnOrder(n, 0);
    vector<int> currentOrder(n, 0);
    vector<int> nodes;

    int previousNode = 0;
    int i = 0;
    double sum = 0;
    double smallestSum = 1e6;
    bool finish = false;

    for (unsigned int i = 0; i < n; i++)
    {
        nodes.push_back(i);
    }

    // This while loop creates all possible permutations of the nodes. We can use this while loop to create an order of ID's visited
    // Let's look for the total path to visit nodes in current node order
    do
    {
        for (auto node : nodes)
        {
            i %= n;
            currentOrder.at(i) = node;
            if (currentOrder.at(0) != start)
            {
                finish = true;
            }
            // std::cout << node << "";

            if (i != 0)
            {
                int sumNode;
                if (node > previousNode)
                {
                    sumNode = node - 1;
                }
                else
                {
                    sumNode = node;
                }
                if (graph.at(previousNode).at(sumNode).second < 0 || isnan(graph.at(previousNode).at(sumNode).second))
                {
                    sum += 99999;
                }
                else
                {
                    sum += graph.at(previousNode).at(sumNode).second;
                }
            }
            i++;
            previousNode = node;
        }

        if (sum < smallestSum && currentOrder.at(0) == start)
        {
            bool check = false;

            for (int x = 0; x < controllers_.size(); x++)
            {
                // CHECK IF CAN BE DONE BY ACKERMAN STEERING:
                pfms::nav_msgs::Odometry odo_current;
                pfms::geometry_msgs::Point goal;
                pfms::nav_msgs::Odometry estimatePose;
                for (int i = 0; i < currentOrder.size() - 1; i++)
                {
                    odo_current.position.x = originaGoals_.at(currentOrder.at(i)).x;
                    odo_current.position.y = originaGoals_.at(currentOrder.at(i)).y;
                    goal = originaGoals_.at(currentOrder.at(i + 1));
                    double time;
                    double distance;

                    if (controllers_.at(x)->checkOriginToDestination(odo_current, goal, distance, time, estimatePose))
                    {
                        check = true;
                    }
                    else
                    {
                        check = false;
                        break;
                    }
                }
            }
            if (check == true)
            {
                smallestSum = sum;
                returnOrder = currentOrder;
            }
        }
        sum = 0;
        // std::cout << "\n\n";

    } while (std::next_permutation(nodes.begin(), nodes.end()) && !finish);

    cout << "\n\nShortest Path:" << endl;
    cout << "Cost: " << smallestSum << endl;
    return returnOrder;
}