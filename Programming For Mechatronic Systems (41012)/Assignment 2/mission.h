#ifndef MISSION_H
#define MISSION_H
#include "missioninterface.h"
#include "pipes.h"
#include "tsp.h"

/*!
 *  \brief     Mission Class Header File
 *  \details
 *  Provides Goals for the controller objects
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning   
 */

#include <vector>
#include <cmath>

class Mission : public MissionInterface
{
public:
  // The Default constructor
  Mission(std::vector<ControllerInterface *> controllers);

  void setGoals(std::vector<pfms::geometry_msgs::Point> goals, pfms::PlatformType platform);

  bool run();

  std::vector<unsigned int> status();

  void setMissionObjective(mission::Objective objective);

  std::vector<double> getDistanceTravelled();

  std::vector<double> getTimeMoving();

  std::vector<std::pair<int, int>> getPlatformGoalAssociation();


protected:
  std::vector<ControllerInterface *> controllers_; //!< A private copy of ControllerInterfaces @sa ControllerInterface
  std::vector<pfms::geometry_msgs::Point> goals_quadcopter_;
  std::vector<pfms::geometry_msgs::Point> goalsAckerman_;

  // FOR GET PLATFORM GOAL ASSOCIATION
  std::vector<std::pair<int, int>> get_platform_association_vector;
  double ackerman_distance = 0; //done
  double ackerman_time = 0;
  double quadcopter_distance = 0;
  double quadcopter_time = 0;

  pfms::PlatformType platform_;
  mission::Objective objective_ = mission::Objective::BASIC;

  // CheckOriginToDestination Parameters:
  pfms::nav_msgs::Odometry odo_current;
  double current_distance_to_goal;
  double time_;
  pfms::nav_msgs::Odometry estimated_goal_pose;

  std::vector<pfms::geometry_msgs::Point> goals_;

  // Clock:
  std::chrono::high_resolution_clock::time_point start_time, end, duration;
};

#endif // RANGERFUSION_H