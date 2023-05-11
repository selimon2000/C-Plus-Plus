#include <iostream>
#include <stack>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef vector<vector<pair<int, double>>> AdjacencyList;

// Printing the graph
void print_adjacency_list(AdjacencyList graph)
{
    // If stack is empty then return
    if (graph.empty())
        return;

    unsigned int nodeNum = 0;
    for (auto edges : graph)
    {
        std::cout << "[" << nodeNum++ << "]" << std::endl;
        for (auto nodes : edges)
        {
            std::cout << nodes.first << ":" << nodes.second << " ";
        }
        std::cout << std::endl;
    }
}

// Printing the path
void print_path(AdjacencyList graph, vector<int> path)
{
    // If graph is empty then return
    if (graph.empty())
        return;

    // If path is empty then return
    if (path.empty())
        return;

    for (unsigned int i = 0; i < path.size() - 1; i++)
    {
        unsigned int node1 = path.at(i);
        unsigned int node2 = path.at(i + 1);
        std::cout << "[" << node1 << "] to ";
        for (unsigned int j = 0; j < graph.at(node1).size(); j++)
        {
            if (graph.at(node1).at(j).first == node2)
            {
                std::cout << "[" << graph.at(node1).at(j).first << "] = " << graph.at(node1).at(j).second << std::endl;
                break;
            }
        }
    }
}

vector<int> brute_force_tsp(AdjacencyList graph, int start)
{
    int n = graph.size();
    vector<int> returnOrder(n, 0);
    vector<int> currentOrder(n, 0);
    vector<int> nodes;
    bool anyStartingPoint = false;

    if (start == -1)
    {anyStartingPoint = true;}
    else if (start >= n || start < -1)
    {
        cout << endl << "START VALUE IS INVALID!!!" << endl << endl;
        return returnOrder;
    }

    double smallestSum = 1e6;

    for (unsigned int i = 0; i < n; i++)
    {nodes.push_back(i);} // if n is 0-3, node is {0,1,2,3}

    // This while loop creates all possible permutations of the> nodes. We can use this while loop to create an order of ID's visited
    // Let's look for the total path to visit nodes in current node order
    while (std::next_permutation(nodes.begin(), nodes.end()))
    {
        double sum = 0;
        int previousNode = 0;

        for (int i = 0; i < n; i++)
        {
            currentOrder.at(i) = nodes.at(i);
            std::cout << nodes.at(i) << "";

            if (i != 0)
            {
                int sumNode;

                if (nodes.at(i) > previousNode)
                {sumNode = nodes.at(i) - 1;}
                else
                {sumNode = nodes.at(i);}

                sum += graph.at(previousNode).at(sumNode).second;
            }
            previousNode = nodes.at(i);
        }

        if (sum < smallestSum && currentOrder.at(0) == start && !anyStartingPoint)
        {
            smallestSum = sum;
            returnOrder = currentOrder;
        }
        else if (sum < smallestSum && anyStartingPoint)
        {
            smallestSum = sum;
            returnOrder = currentOrder;
        }

        std::cout << "\n";
    }

    cout << "\n\nShortest Path Cost: " << smallestSum << endl;
    return returnOrder;
}

int main()
{
    // Build the graph
    AdjacencyList graph = {
        {{1, 50}, {2, 80}, {3, 40}},  // Node 0 is connected to nodes 1,2 and 3 (via edges with weights)
        {{0, 50}, {2, 10}, {3, 100}}, // Node 1 is connected to nodes 0,2 and 3 (via edges)
        {{0, 80}, {1, 10}, {3, 20}},  // Node 2 is connected to ....
        {{0, 40}, {1, 100}, {2, 20}}, // Node 3 is connected to ....
    };

    print_adjacency_list(graph);
    cout << "Brute Force Permutations:" << endl;
    vector<int> path = brute_force_tsp(graph, 2); // in this example, we don't care about where the node starts from, and we are simply looking for the shortest parth
    cout << "Printing Shortest Path: " << endl;
    print_path(graph, path);
}