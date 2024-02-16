#include "quadcopter.h"
#define _USE_MATH_DEFINES

/*!
 *  \brief     Quadcopter Class Implementation File
 *  \details
 *  Runs the functions to ensure quadcopter moves to the goals.
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning
 */

// Default constructor should set all sensor attributes to a default value
Quadcopter::Quadcopter()
{
  // Setting type as Quadcopter as car is being used
  type = pfms::PlatformType::QUADCOPTER;
  // update current position
  getOdometry();
  ready_ = false;

  // VARIABLES From .h file:
  //  UAV INPUTS
  move_l_r = 0;
  move_f_b = 0;
  // SYSTEM
  status_ = pfms::PlatformStatus::IDLE;
  // THREADING
  ready_ = false;
  tolerance_=0.5;
}

Quadcopter::~Quadcopter()
{
  ready_ = false;
  quadcopter_thread->join();
  delete quadcopter_thread;
}

// Returns how long it takes to get car to goal
double Quadcopter::timeToGoal()
{return current_distance_to_goal / UAV_VELOCITY_XY;}

void Quadcopter::calculations()
{
  double delta_x = (goal_x - odo_current.position.x);
  double delta_y = (goal_y - odo_current.position.y);
  double target_angle = atan2(delta_y, delta_x);

  current_distance_to_goal = sqrt(pow(delta_x, 2) + pow(delta_y, 2));

  move_l_r = sin(target_angle) * UAV_VELOCITY_XY;
  move_f_b = cos(target_angle) * UAV_VELOCITY_XY;
}

// by checking the angle, If allowable, true is returned, and goal is saved into goalX and goalY
// Also calculates time and distance.
bool Quadcopter::checkOriginToDestination(pfms::nav_msgs::Odometry origin, pfms::geometry_msgs::Point goal, double &distance, double &time, pfms::nav_msgs::Odometry &estimated_goal_pose)
{
  // Create private copy of goals
  goal_x = goal.x;
  goal_y = goal.y;

  odo_current = origin;
  yaw = odo_current.yaw;
  calculations();

  distance = distanceToGoal();
  time = timeToGoal();

  estimated_goal_pose.position.x = goal.x;
  estimated_goal_pose.position.y = goal.y;
  estimated_goal_pose.yaw = yaw;

  // WITH QUADCOPTER, ANY POSITION CAN BE ACHIEVED
  return true;
}

void Quadcopter::run()
{
  status_ = pfms::PlatformStatus::RUNNING;
  ready_ = true;
  quadcopter_thread = new std::thread(&Quadcopter::reachGoals, this);
}

void Quadcopter::quadcopterControlWhile(double distance__, double velocity)
{
  while (current_distance_to_goal > distance__)
  {
    UAV_VELOCITY_XY = 1;
    prev_odo = odo_current;

    getOdometry();
    calculations();

    // Ensuring that always 2m high
    if (odo_current.position.z < 1.99)
    {move_u_d = 0.05;}
    else if (odo_current.position.z > 2.01)
    {move_u_d = -0.05;}
    // Ensuring that yaw is always '0':
    if (odo_current.yaw < 0)
    {turn_l_r = 0.1;}
    else if (odo_current.yaw > 0)
    {turn_l_r = -0.1;}
    pfms::commands::UAV uav{++seq, turn_l_r, move_l_r, move_u_d, move_f_b};
    pipesPtr->send(uav);

    distance_travelled_ += std::hypot(odo_current.position.x - prev_odo.position.x, odo_current.position.y - prev_odo.position.y);
  }
}

void Quadcopter::reachGoals()
{
  start_time = std::chrono::high_resolution_clock::now();
  double v;

  pipesPtr->send(pfms::PlatformStatus::TAKEOFF);
  status_ = pfms::PlatformStatus::RUNNING;

  for (int i = 0; i < goals_.size(); i++)
  {
    std::cout << "PRINTING GOAL LOCATIONS: " << goals_.at(i).x << " " << goals_.at(i).y << std::endl;

    checkOriginToDestination(getOdometry(), goals_.at(i), distance, time, estimate_odo);
    calculations();

    quadcopterControlWhile(7,8);
    quadcopterControlWhile(5,3.5);
    quadcopterControlWhile(3*tolerance_,0.8);
    quadcopterControlWhile(tolerance_,0.4);

    pfms::commands::UAV brake{++seq, 0, 0, 0, 0};
    pipesPtr->send(brake);
  }
  ready_ = false;
  pipesPtr->send(pfms::PlatformStatus::LANDING);
  status_ = pfms::PlatformStatus::IDLE;
}

pfms::PlatformStatus Quadcopter::status()
{return status_;}