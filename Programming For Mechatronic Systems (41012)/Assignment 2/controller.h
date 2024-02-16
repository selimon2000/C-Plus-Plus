#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "controllerinterface.h"
#include "pipes.h"
#include <iostream>


/*!
 *  \brief     Controlller Class Header File
 *  \details
 *  Creates an object of either the Ackerman or Quadcopter platform, and controls its kinematics.
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning   
 */



using pfms::commands::UAV;
using pfms::commands::UGV;
using std::vector;

class Controller : public ControllerInterface
{
public:
  // Default constructors should set all sensor attributes to a default value
  Controller();

protected:

  bool setGoals(std::vector<pfms::geometry_msgs::Point> goals);

  pfms::PlatformType getPlatformType();

  double distanceToGoal();

  bool setTolerance(double tolerance);

  double distanceTravelled(void);

  double timeTravelled(void);

  pfms::nav_msgs::Odometry getOdometry();

  virtual pfms::PlatformStatus status(void) = 0;

  virtual void run(void) = 0;

  virtual bool checkOriginToDestination(pfms::nav_msgs::Odometry origin,pfms::geometry_msgs::Point goal,double &distance,double &time,pfms::nav_msgs::Odometry &estimatedGoalPose) = 0;

  Pipes *pipesPtr = new Pipes();

  pfms::geometry_msgs::Point target;
  pfms::PlatformType type;
  std::vector<double> distance;
  pfms::nav_msgs::Odometry odo_current;

  double current_distance_to_goal;
  double total_distance_travelled;
  double distance_travelled_;

  // TIME:
  std::chrono::high_resolution_clock::time_point start_time, end, duration;
  double time_;
  double tolerance_;

  pfms::nav_msgs::Odometry estimated_goal_pose;

  // universal (for both car and drone) values of odometry
  double goal_x, goal_y;
  double yaw;
  std::vector<pfms::geometry_msgs::Point> goals_;

private:
};

#endif // CONTROLLER_H