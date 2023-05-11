#ifndef QUADCOPTER_H
#define QUADCOPTER_H
#include "controller.h"

/**
 * @brief Runs the functions to ensure quadcopter moves to the goals.
 */

/*!
 *  \brief     Quadcopter Class Heaader File
 *  \details
 *  Runs the functions to ensure quadcopter moves to the goals.
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning   
 */



#include <cmath>

class Quadcopter : public Controller
{
public:

  /**
  Default constructor sets all variables to a default value
  */
  Quadcopter();

  /**
  Deconstructor enseures thread finishes and does not run again, and is deleted
  */
  ~Quadcopter();

  double timeToGoal(void);

  bool checkOriginToDestination(pfms::nav_msgs::Odometry origin, pfms::geometry_msgs::Point goal, double &distance, double &time, pfms::nav_msgs::Odometry &estimated_goal_pose);

 /**
  Function ensures that quadcopter reaches destination of all elements in goals_ vector, whilst also calculating the distance travelled.
  */
  void reachGoals(void);

  pfms::PlatformStatus status(void);

protected:
/**
  //CONSTANTS:
*/
  double UAV_VELOCITY_XY = 1; //!< MAX Velocity set (ignoring z velocity), can go faster by changing this value
/**
  //VARIABLES:
*/ 
   // UAV INPUTS
    double move_f_b; //!< Velocity of quadcopter in the y direction.
    double move_l_r; //!< Velocity of quadcopter in the y direction.
    double move_u_d = 0;
    double turn_l_r = 0;
    double distance = 0;
    double time = 0;
    unsigned long int seq = 0;
     pfms::nav_msgs::Odometry estimate_odo;
  pfms::nav_msgs::Odometry prev_odo;

    // SYSTEM
    pfms::PlatformStatus status_; //!< The current status of the platform, either RUNNING or IDLE
    // THREADING
    std::atomic<bool> ready_; //!< To determine if threaded function should run or not
    std::thread *quadcopter_thread; //!< Thread


private:
  Pipes *pipesPtr = new Pipes();

  /**
  Calculations which are performed when quadcopter is both running and not running. Unlike Ackerman, the calculations are constant as 
  the velocitites can be recalculated as it is travelling.

  The quadcopter maintains a constant yaw, and moves in the x and y plane, moving both in the x and y direction simulataneously, with velocities inputted as
  move_f_b & move_l_r
  */
  void calculations();

  /**
  Function used to start the thread, so that reachGoals() is enabled, and therefore quadcopter can go to locations.
  */
  void run();

  void quadcopterControlWhile(double distance__, double velocity);
  
};

#endif // ACKERMAN_H