#include "ackerman.h"
/*!
 *  \brief     Ackerman Class Implementation File
 *  \details
 *  Runs the functions to ensure Audi moves to the goals.
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning
 */

// Default constructor should set all sensor attributes to a default value

Ackerman::Ackerman()
{
  // Setting type as ACKERMAN as car is being used
  type = pfms::PlatformType::ACKERMAN;
  // update current position
  getOdometry();
  // FOR CAR STEERING CALCULATIONS
  heading_difference = 0;
  linear_distance_to_goal = 0;
  steering_angle = 0;
  input_steering_angle = 0;
  radius = 0;
  // BOOL FOR TYPE OF CALCULATION IMPLEMENTED
  running_ = false;
  // FOR CAR DISTANCE CALCULATION
  alpha = 0;
  prev_odo;
  // CAR STATUS
  status_ = pfms::PlatformStatus::IDLE;
  // THREADING
  ready_ = false;
}

Ackerman::~Ackerman()
{
  ready_ = false;
  ackerman_thread->join();
  delete ackerman_thread;
}

// Returns how long it takes to get car to goal
double Ackerman::timeToGoal()
{ return current_distance_to_goal / CAR_TOP_SPEED;}

void Ackerman::calculationsWithBool(bool running)
{
  double delta_x = (goal_x - odo_current.position.x);
  double delta_y = (goal_y - odo_current.position.y);
  yaw = odo_current.yaw;

  // Calculating Linear Distance to Goal:
  linear_distance_to_goal = hypot(delta_x, delta_y);
  // Calculating Heading Difference:
  heading_difference = atan2(delta_y, delta_x) - yaw;
  // Calculating Radius:
  radius = linear_distance_to_goal / (2 * sin(heading_difference));
  // Calculating Arc Distance to Goal, where the car will actually travel:
  current_distance_to_goal = fabs(radius * 2 * heading_difference);
  
  //Calculating alpha:
  double dot = (std::cos(prev_odo.yaw) * std::cos(odo_current.yaw)) + (std::sin(prev_odo.yaw) * std::sin(odo_current.yaw));
  double det = (std::cos(prev_odo.yaw) * std::sin(odo_current.yaw)) - (std::sin(prev_odo.yaw) * std::cos(odo_current.yaw));
  alpha = std::atan2(det, dot);

  // Calculating Steering Angle:
  steering_angle = atan((2 * WHEEL_BASE * sin(heading_difference)) / linear_distance_to_goal);
  // Calculate the actual angle which should be inputted into the steering wheel of the car:
  input_steering_angle = steering_angle * STEERING_RATIO;
}

// by checking the angle, if allowable, true is returned, and goal is saved into goalX and goalY
// Also calculates time and distance.
bool Ackerman::checkOriginToDestination(pfms::nav_msgs::Odometry origin, pfms::geometry_msgs::Point goal, double &distance, double &time, pfms::nav_msgs::Odometry &estimated_goal_pose)
{
  // Create private copy of goals
  goal_x = goal.x;
  goal_y = goal.y;

  odo_current = origin;
  // check if steering angle is allowable
  yaw = odo_current.yaw;

  running_ = false;
  calculationsWithBool(running_);

  if (fabs(steering_angle) <= MAX_STEERING_ANGLE)
  {
    distance = distanceToGoal();
    time = timeToGoal();

    // Calculating estimated_goal_pose of the robot, where the yaw is to be calculated
    estimated_goal_pose.position.x = goal.x;
    estimated_goal_pose.position.y = goal.y;
    estimated_goal_pose.yaw = origin.yaw + 2 * heading_difference;

    if (estimated_goal_pose.yaw > M_PI)
      estimated_goal_pose.yaw -= 2 * M_PI;
    else if (estimated_goal_pose.yaw < -M_PI)
      estimated_goal_pose.yaw += 2 * M_PI;
    // update total distance travelled
    total_distance_travelled += distance;
    return true;
  }
  else
  {
    distance = -1;
    time = -1;
    return false;
  }
}

void Ackerman::run()
{
  status_ = pfms::PlatformStatus::RUNNING;
  // reachgoals will only run when run function gets called with threading;
  ackerman_thread = new std::thread(&Ackerman::reachGoals, this);
  ready_ = true;
}

// This function was replaces as for some reason I cannot reach the goal within a 0.5m threshoold

void Ackerman::reachGoals()
{
  running_ = false;
  calculationsWithBool(running_);
  // TIME
  start_time = std::chrono::high_resolution_clock::now();

  pfms::nav_msgs::Odometry estimateOdo;
  double distance = 0;
  double time = 0;
  double v = 0;
  unsigned long int seq = 0;

  for (int i = 0; i < goals_.size(); i++)
  {
    std::cout << "New Goal at" << goals_.at(i).x << ", " << goals_.at(i).y << std::endl;
    checkOriginToDestination(getOdometry(), goals_.at(i), distance, time, estimateOdo);
    calculationsWithBool(running_);

    // STEP 1: GO CLOSE TO GOAL
    while (linear_distance_to_goal > 6.5)
    {
      v = sqrt(pow(odo_current.linear.x, 2) + pow(odo_current.linear.y, 2));
      // std::cout << "Steering Angle:" << steering_angle << std::endl;
      prev_odo = odo_current;
      getOdometry();
      running_ = true;
      calculationsWithBool(running_);

      if (fabs(steering_angle) < 0.11)
      {velocityControl(3.5);}
      else if (fabs(steering_angle) < 0.2)
      {velocityControl(3.2);}
      else
      {velocityControl(2.9);}

            {
        std::unique_lock<std::mutex> lck(numMutexDistance);
        distance_travelled_ += std::abs(alpha * radius);
      }
    }

    while (linear_distance_to_goal > 3*tolerance_)
    {
      v = sqrt(pow(odo_current.linear.x, 2) + pow(odo_current.linear.y, 2));

      prev_odo = odo_current;
      getOdometry();
      running_ = true;
      calculationsWithBool(running_);
      if (v > 2.7*1.1)
      {
        UGV ugv{++seq, MAX_BRAKE_THROTTLE/2, input_steering_angle, 0};
        pipes_ptr->send(ugv);
      }
      else
      {
        UGV ugv{++seq, 0, input_steering_angle, DEFAULT_THROTTLE};
        pipes_ptr->send(ugv);
      }
      {
        std::unique_lock<std::mutex> lck(numMutexDistance);
        distance_travelled_ += std::abs(alpha * radius);
      }
    }

    while (linear_distance_to_goal > tolerance_)
    {
      v = sqrt(pow(odo_current.linear.x, 2) + pow(odo_current.linear.y, 2));

      prev_odo = odo_current;
      getOdometry();
      running_ = true;
      calculationsWithBool(running_);
      if (v > 1.9*1.1)
      {
        UGV ugv{++seq, MAX_BRAKE_THROTTLE / 2, input_steering_angle, 0};
        pipes_ptr->send(ugv);
      }
      else
      {
        UGV ugv{++seq, 0, input_steering_angle, DEFAULT_THROTTLE};
        pipes_ptr->send(ugv);
      }

      {
        std::unique_lock<std::mutex> lck(numMutexDistance);
        distance_travelled_ += std::abs(alpha * radius);
      } 
        v = sqrt(pow(odo_current.linear.x, 2) + pow(odo_current.linear.y, 2));
    }
    // STEP 2: BRAKE AFTER REACHING TOLERANCE
    while (v > 0.0005)
    {
      prev_odo = odo_current;
      getOdometry();
      UGV ugv{++seq, MAX_BRAKE_THROTTLE, input_steering_angle, 0};
      pipes_ptr->send(ugv);
      v = sqrt(pow(odo_current.linear.x, 2) + pow(odo_current.linear.y, 2));

      {
        std::unique_lock<std::mutex> lck(numMutexDistance);
        distance_travelled_ += std::abs(alpha * radius);
      }
    }
  }
  // STEP 2: BRAKE AFTER REACHING TOLERANCE
  while (v > 0.01)
  {
    prev_odo = odo_current;
    getOdometry();
    UGV ugv{++seq, MAX_BRAKE_THROTTLE, input_steering_angle, 0};
    pipes_ptr->send(ugv);
    v = sqrt(pow(odo_current.linear.x, 2) + pow(odo_current.linear.y, 2));

          {
        std::unique_lock<std::mutex> lck(numMutexDistance);
        distance_travelled_ += std::abs(alpha * radius);
      }
  }
  running_ = false;
  {
    std::unique_lock<std::mutex> lck(numReadyMutex);
    ready_ = false;
  }
  status_ = pfms::PlatformStatus::IDLE;
}

pfms::PlatformStatus Ackerman::status()
{ return status_;}

void Ackerman::velocityControl(double velocity)
{
  v = sqrt(pow(odo_current.linear.x, 2) + pow(odo_current.linear.y, 2));

  if (v < velocity)
  {
    UGV ugv{++seq, 0, input_steering_angle, DEFAULT_THROTTLE};
    pipes_ptr->send(ugv);
  }
  else
  {
    UGV ugv{++seq, 4, input_steering_angle, 0};
    pipes_ptr->send(ugv);
  }
}