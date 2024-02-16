#ifndef TSP_H
#define TSP_H
#include "controllerinterface.h"

/**
 * @brief Calculates The TSP (Travelling Salesman Problem) so that both the ackerman (audi) and quadcopter travel with the most optimised path.
 *  The calculations use brute force, where it searches all possible permuations, and uses the one which costs less, whilst being possible for both platforms.
 */

/*!
 *  \brief     TSP Class Header File
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


using namespace std;
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include <string>
#include <typeinfo>

typedef vector<vector<pair<int, double>>> AdjacencyList;

class TSP
{
public:
  TSP(std::vector<ControllerInterface *> controllers);

  /**
  Calculates the optimised vector of points which the quadcopter should take to travel to destinations, where distance efficiency is key
  The graph AKA Adjacency list is converted from originalGoals here.
  @param[in] originalGoals The given goals
  @param[in] origin Where the platform currently is, as it is important to calculate distnace based on the current location of the platform.
  The current odometry is passed as a point to the goals
  @return std::vector<pfms::geometry_msgs::Point with ordered goals, where the first Point in the vector is where the platform will travel initially,
          and the last Point in the vector is where the platform will finish
  */
  std::vector<pfms::geometry_msgs::Point> advancedMode(std::vector<pfms::geometry_msgs::Point> originalGoals, pfms::nav_msgs::Odometry origin);

  /**
  Calculates the optimised vector of points which the ackerman (audi) should take to travel to destinations, where distance efficiency is key.
  @param[in] originalGoals The given goals
  @param[in] origin Where the platform currently is, as it is important to calculate distnace based on the current location of the platform.
    The current odometry is passed as a point to the goals

  @return std::vector<pfms::geometry_msgs::Point with ordered goals, where the first Point in the vector is where the platform will travel initially,
          and the last Point in the vector is where the platform will finish
  */
  std::vector<pfms::geometry_msgs::Point> advancedModeCarNew(vector<pfms::geometry_msgs::Point> originalGoals, pfms::nav_msgs::Odometry origin);

  /**
  Gives Ackerman and Qaudcopter goals, where distance efficiency is key.
  */
  std::vector<pfms::geometry_msgs::Point> superMode();


protected:
  std::vector<ControllerInterface *> controllers_; //!< A private copy of ControllerInterfaces @sa ControllerInterface
  std::vector<pfms::geometry_msgs::Point> originaGoals_;

private:
  /**
  Prints the path the platform should take, indicating the cost of each 'trip'
  @param[in] graph
  @param[in] path The most efficient goal path calculated by brute force function
  */
  void printPath(AdjacencyList graph, vector<int> path);
  
  /**
  Prints the Adjacency Graph, in the form of: vector<vector<pair<int, double>>>
  Where the Adjacency Graph is created in the advancedMode()
  @param[in] graph
  */
  void printAdjacencyList(AdjacencyList graph);

  /**
  Given an adjacency list, it computes which point in the graph should go in what order for optimum efficiency
  @param[in] graph The origin pose, specified as odometry for the platform
  @param[in] start This tells which point the calculations should start from. In this method, the current odometry is passed as a point to the goals, so
                    it is very important that start=0;
  @return vector<int>, where vector.at(0) indicates starting point, and vector.at(1) indicates end point
  */
  vector<int> bruteForceTSP(AdjacencyList graph, int start);



};

#endif // ACKERMAN_H