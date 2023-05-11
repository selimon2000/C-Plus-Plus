#include "controller.h"



/*!
 *  \brief     Controlller Class Implementation File
 *  \details
 *  Creates an object of either the Ackerman or Quadcopter platform, and controls its kinematics.
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning   
 */



// Default constructors should set all sensor attributes to a default value
Controller::Controller()
{ start_time = std::chrono::high_resolution_clock::now();
  current_distance_to_goal = 0;
  total_distance_travelled = 0;
  distance_travelled_ = 0;
  time_ = 0 ;
  tolerance_ = 0;
  goal_x = 0;
  goal_y = 0;
  yaw = 0;

}

// Purpose is to check if goal is suitable before running it
bool Controller::setGoals(std::vector<pfms::geometry_msgs::Point> goals)
{
  goals_ = goals;
  bool check = true;
  pfms::nav_msgs::Odometry currentPose;

  currentPose = getOdometry();

  for (int i = 0; i < goals.size(); i++)
  {
    check = checkOriginToDestination(odo_current, goals.at(i), current_distance_to_goal, time_, estimated_goal_pose);
    if (check == true)
      {currentPose = estimated_goal_pose;
      odo_current.position.x = goals.at(i).x;
      odo_current.position.y = goals.at(i).y;}
    else
      {check=false;}
  }
  return check;
}

// Platform type deteremines if it's a ugv or uav
pfms::PlatformType Controller::getPlatformType()
{return type;}

// getter for distance to goal, from current position to target
double Controller::distanceToGoal()
{return current_distance_to_goal;}

// setter for tolerance, set in unit tests
bool Controller::setTolerance(double tolerance)
{
  tolerance_ = tolerance;
  return true;
}

// getter function, returning totalDistanceTravelled
double Controller::distanceTravelled()
{return distance_travelled_;}

double Controller::timeTravelled()
{
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> duration = end - start_time;
  long double elapsed_time = (long double)duration.count();
  return elapsed_time;
}

// Returns current odometry information
pfms::nav_msgs::Odometry Controller::getOdometry()
{
  pfms::nav_msgs::Odometry odo1;
  pipesPtr->read(odo1, type);
  odo_current = odo1;
  return odo_current;
}