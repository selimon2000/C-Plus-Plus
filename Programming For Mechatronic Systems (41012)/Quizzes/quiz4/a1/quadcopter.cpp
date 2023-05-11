#include "quadcopter.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

///////////////////////////////////////////////////////////////
//! @todo
//! TASK 1 - Initialisation
//!
//! Is there anything we need to initialise in the Constructor?

Quadcopter::Quadcopter() : TARGET_SPEED(0.4)
{
    tolerance_ = 0.5; // We set tolerance to be default of 0.5

    // DistanceToGoal shoudl be 0
    // TimeToGoal should be 0
    goal_.distance = 0;
    goal_.time = 0;
    // TimeInMotion should be 0
    time_travelled_ = 0;
    // DistanceTravelled should be 0
    distance_travelled_ = 0;
    // PlatformType should be pfms::PlatformType::QUADCOPTER
    type_ = pfms::PlatformType::QUADCOPTER;
    // If we call getOdometry we expect it to return the location we set as initial odometry
    odo_ = getOdometry();
};

// We delete the pipes here specifically, which forces them to close before the object is terminated
Quadcopter::~Quadcopter()
{
    delete pipesPtr_;
}

bool Quadcopter::checkOriginToDestination(pfms::nav_msgs::Odometry origin, pfms::geometry_msgs::Point goal,
                                          double &distance, double &time,
                                          pfms::nav_msgs::Odometry &estimatedGoalPose)
{

    // Use pythagorean theorem to get direct distance to goal
    double dx = goal.x - origin.position.x;
    double dy = goal.y - origin.position.y;

    distance = std::hypot(dx, dy);
    time = distance / TARGET_SPEED;

    // The estimated goal pose would be the goal, at the angle we had at the origin
    // as we are not rotating the platform, simple moving it left/right and fwd/backward
    estimatedGoalPose.position.x = goal.x;
    estimatedGoalPose.position.y = goal.y;
    estimatedGoalPose.yaw = origin.yaw;
    estimatedGoalPose.linear.x = 0;
    estimatedGoalPose.linear.y = 0;

    return true;
}
bool Quadcopter::calcNewGoal(void)
{
    // getOdometry(); // This will update internal copy of odometry, as well as return value if needed.
    odo_ = getOdometry();

    pfms::nav_msgs::Odometry est_final_pos;

    if (!checkOriginToDestination(odo_, goal_.location, goal_.distance, goal_.time, est_final_pos))
        return false;

    // Calculate absolute travel angle required to reach goal
    double dx = goal_.location.x - odo_.position.x;
    double dy = goal_.location.y - odo_.position.y;

    currentdistance = sqrt(pow(dx, 2) + pow(dy, 2));

    target_angle_ = std::atan2(dy, dx);

    return true;
}

void Quadcopter::sendCmd(double turn_l_r, double move_l_r, double move_u_d, double move_f_b)
{
    pfms::commands::UAV cmd = {
        cmd_pipe_seq_++,
        turn_l_r,
        move_l_r,
        move_u_d,
        move_f_b,
    };
    pipesPtr_->send(cmd);
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to ensure message sent
}

bool Quadcopter::reachGoal(void)
{
    calcNewGoal(); // account for any drift between setGoal call and now, by getting odo and angle to drive in
    pfms::nav_msgs::Odometry prev_odo = odo_;
    auto start_time = std::chrono::system_clock::now();
    double estimated_time_to_reach_goal = goal_.time;

    // FIRST: TAKEOFF:
    if (odo_.position.z < 0.5)
    {
        pipesPtr_->send(pfms::PlatformStatus::TAKEOFF);
    }

    // Run below loop until we reach goal
    while (!goalReached())
    {
        //! TASK 2 - Completion of task requires sending correct values in sendCmd
        //! We have access following variables:
        //! odo_ - current odometry
        //! target_angle_ - the desired direction of travel
        //! AND  const TARGET_SPEED which is target speed (0.4ms/s)
        //!
        //! We need to compute dx and dy - the portion of the control in the two axis
        //! in below we just use 0.1 which will not work, it will fly at 45deg

        //  Calculating Heading Difference:
        pfms::nav_msgs::Odometry prev_odo = odo_;
        calcNewGoal(); // get odometry and update target angle of control
        // getOdometry();

        double dy = sin(target_angle_) * 0.4;
        double dx = cos(target_angle_) * 0.4;

        // Ensuring that yaw is always '0':
        if (odo_.yaw < 0)
        {
            turn_l_r = 0.1;
            std::cout << "Turning Anti clockwise " << odo_.yaw << std::endl;
        }
        else if (odo_.yaw > 0)
        {
            turn_l_r = -0.1;
            std::cout << "Turning clockwise " << odo_.yaw << std::endl;
        }
        else
        {
            turn_l_r = 0;
            std::cout << "NOT TURNING AT ALL!" << odo_.yaw << std::endl;
        }

        // Check the syntax of the command, for left/right and forward/backward
        sendCmd(turn_l_r, dy, 0, dx);

        /////////////////////////////////////////////////////////////////
        // We check if we have not reached goal in close to anticipated time (2s margin)
        // if not reachGoal should be aborted
        double time_since_starting = timeLapsed(start_time);

        // std::cout << "[est/cur] time to goal [" << estimated_time_to_reach_goal << "/" << time_since_starting << "]" << std::endl;

        if (time_since_starting > (estimated_time_to_reach_goal + 2.0))
        {
            // If we have not reached it in the designated time we abandon reaching goal
            // For TASK 3 and 4, consider if anything else needs updating
            time_travelled_ = timeLapsed(start_time);

            return false;
        }

        ///////////////////////////////////////////////////////////////
        //! @todo
        //! TASK 4 - Update distance travelled
        //!
        //! While the estimated distance at the begining is a rough guide
        //! As the platform moves it could travel more, especially if it
        //! was going against wind (and in case of Ackerman if it was drifting)
        //! Your better of incremeting distance travelled as you go along
        //!
        //! We have access to following variables
        //! odo_ - current position of platform
        //! prev_odo - the previous position
        //! distance_travelled_ - the distance travelled thus far
        calcNewGoal(); // get odometry and update target angle of control

        double changeInX = fabs(odo_.position.x - prev_odo.position.x);
        double changeInY = fabs(odo_.position.y - prev_odo.position.y);
        distance_travelled_ += std::hypot(changeInX, changeInY);
        // distance_travelled_ = std::hypot(changeInX, changeInY);

        // std::cout << "Distance Travelled: " << distance_travelled_ << std::endl;
        //////////////////////////////////////////////////////////////////
    }

    // Stop thq quadcopter immediately
    sendCmd(0, 0, 0, 0);

    // pipesPtr_->send(pfms::PlatformStatus::LANDING);

    calcNewGoal(); // get odometry and update distance to goal

    ///////////////////////////////////////////////////////////////
    //! @todo
    //! TASK 3 - Update time travelled
    //!
    //! We have access following variables
    //! start_time - the time reaching the goal was started
    //! time_travelled_ - the time we have travelled thus far
    //!
    //! Look at how we compute wether to abort reachGoal
    //! as you could use the same function
    //! Also, consider, if we aborted the function reachGoal, should we
    //! update the time travelled?

    //////////////////////////////////////////////////////////////////
    time_travelled_ = timeLapsed(start_time);
    // std::cout<<"Time Travelled: "<<time_travelled_<<std::endl;
    return true;
}

double Quadcopter::timeLapsed(std::chrono::time_point<std::chrono::system_clock> start_time)
{
    // Update time taken
    auto finish_time = std::chrono::system_clock::now();
    // std::chrono::seconds is integer for some reason, thus duration<double>
    auto time_taken = std::chrono::duration_cast<std::chrono::duration<double>>(finish_time - start_time);
    return time_taken.count();
}