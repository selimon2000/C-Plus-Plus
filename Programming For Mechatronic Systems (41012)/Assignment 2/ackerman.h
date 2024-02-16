#ifndef ACKERMAN_H
#define ACKERMAN_H
#include "controller.h"

/**
 * @brief Runs the functions to ensure ackerman platform(audi) moves to the goals.
 */

/*!
 *  \brief     Ackerman Class Header File
 *  \details
 *  Runs the functions to ensure Audi moves to the goals.
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning   
 */



#include <cmath>
#define _USE_MATH_DEFINES
using namespace std;

class Ackerman : public Controller
{
public:
  /**
  Default constructor sets all variables to a default value
  */
  Ackerman();

  /**
  Deconstructor enseures thread finishes and does not run again, and is deleted
  */
  ~Ackerman();

  double timeToGoal();

  bool checkOriginToDestination(pfms::nav_msgs::Odometry origin, pfms::geometry_msgs::Point goal, double &distance, double &time, pfms::nav_msgs::Odometry &estimated_goal_pose);

 /**
  Function ensures that ackerman (audi) reaches destination of all elements in goals_ vector, whilst also calculating the distance travelled.
  */
  void reachGoals();

  pfms::PlatformStatus status();

  double computeRadius(pfms::nav_msgs::Odometry origin, pfms::geometry_msgs::Point goal);

protected:
 /**
Constant Variables For Audi Vehicle in Simulation, Specified by Assignment Proformer
*/
  static constexpr double STEERING_RATIO = 17.3;
  static constexpr double LOCK_TO_LOCK_REVS = 3.2;
  static constexpr double TRACK_WIDTH = 1.638;
  static constexpr double WHEEL_RADIUS = 0.36;
  static constexpr double WHEEL_BASE = 2.65;
  static constexpr double MAX_BRAKE_THROTTLE = 8000;
  static constexpr double DEFAULT_THROTTLE = 0.5;
  static constexpr double MAX_STEERING_ANGLE = M_PI * LOCK_TO_LOCK_REVS / STEERING_RATIO;
  static constexpr double CAR_TOP_SPEED = 2.91;

/**
  Variables which change
*/
  // FOR CAR STEERING CALCULATIONS
  double heading_difference;
  double linear_distance_to_goal; //The hypotenuse between the platform position and goal.
  double steering_angle; //!< Steering angle of car centre (imaginary tire)
  double input_steering_angle; //!< Steering angle of steering angle to be inputted into pipes, which is the realistic steering angle which the driver will input into the steering wheel. This is steering_angle x steering ratio.
  double radius; //!< Radius of car turn

  bool running_;  //!< OOL FOR TYPE OF CALCULATION IMPLEMENTED in Calculations
  // FOR CAR DISTANCE CALCULATION
  double alpha; //!< Used to calculate curvillinear distance travelled, which the platform will take
  pfms::nav_msgs::Odometry prev_odo; //!< Every time the platform moves, the old position (prev_odo) is compared to the new position (odo_current) to calculate distance travelled.
  // CAR STATUS
  pfms::PlatformStatus status_; //!< The current status of the platform, either RUNNING or IDLE
  // THREADING
  std::atomic<bool> ready_;  //!< To determine if threaded function should run or not
  std::thread *ackerman_thread; //!< Thread
  double distance_to_goal;
  double time_to_goal_;
    double v = 0;
  unsigned long int seq =0;
  void calculationsWithBool(bool running);
  void calculations();

private:
  Pipes *pipes_ptr = new Pipes();
  std::mutex numReadyMutex;
  std::mutex numMutexDistance;

  /**
  The calculations which are performed when audi is both running and not running are different, and determined with bool running.
  */
  void velocityControl(double velocity);
  void getYawOnly();



  /**
  Function used to start the thread, so that reachGoals() is enabled, and therefore quadcopter can go to locations.
  */
  void run();


};

#endif // ACKERMAN_H