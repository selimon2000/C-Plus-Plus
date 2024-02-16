#include "mission.h"
#include "tsp.h"
/*!
 *  \brief     Mission Class Implementation File
 *  \details
 *  Provides Goals for the controller objects
 *  \author    Selimon Shukurzad
 *  \version   1.0
 *  \date      05-02-2023
 *  \pre       none
 *  \bug       none reported as of 05-02-2023
 *  \warning
 */

Mission::Mission(std::vector<ControllerInterface *> controllers)
{
    // copying controllers into private
    controllers_ = controllers;
    auto start_time = std::chrono::high_resolution_clock::now();
    objective_ = mission::Objective::BASIC;
}

void Mission::setGoals(std::vector<pfms::geometry_msgs::Point> goals, pfms::PlatformType platform)
{
    goals_ = goals;
    platform_ = platform;
    int goalSize = goals_.size();
    int controllerSize = controllers_.size();

    if (platform_ == pfms::PlatformType::QUADCOPTER)
    {
        goals_quadcopter_ = goals_;
        if (objective_ == mission::Objective::ADVANCED)
        {
            TSP tsp(controllers_);
            goals_quadcopter_ = tsp.advancedMode(goals, controllers_.at(0)->getOdometry());
        }
        std::cout << "PRINTING" << endl;
        for (int i = 0; i < goals_quadcopter_.size(); i++)
        {
            cout << goals_quadcopter_.at(i).x << ", " << goals_quadcopter_.at(i).y << std::endl;
        }

        for (int i = 0; i < controllerSize; i++)
        {
            std::vector<double> quadcopterDistanceVector;
            odo_current=controllers_.at(i)->getOdometry();

            for (int j = 0; j < goals_quadcopter_.size(); j++)
            {
                if (controllers_.at(i)->checkOriginToDestination(odo_current, goals_quadcopter_.at(j), current_distance_to_goal, time_, estimated_goal_pose))
                {
                    odo_current = estimated_goal_pose;
                    quadcopter_distance += current_distance_to_goal;
                    quadcopterDistanceVector.push_back(current_distance_to_goal);
                    quadcopter_time += time_;
                }
                else if (controllers_.at(i)->checkOriginToDestination(odo_current, goals_quadcopter_.at(j), current_distance_to_goal, time_, estimated_goal_pose))
                {
                    std::cout << "Quadcopter Goal Being Deleted" << std::endl; // THIS SHOULD NEVER HAPPEN COS QUADCOPTER SHOULD ACCEPT ANY GOAL
                    goals_quadcopter_.erase(goals_quadcopter_.begin() + j);    // DELETE
                }
            }
        }
    }
    else if (platform_ == pfms::PlatformType::ACKERMAN)
    {
        goalsAckerman_ = goals_;
        if (objective_ == mission::Objective::ADVANCED)
        {
            TSP tsp(controllers_);
            goalsAckerman_ = tsp.advancedModeCarNew(goals_, controllers_.at(0)->getOdometry());
        }

        for (int i = 0; i < controllers_.size(); i++)
        {
            std::vector<double> ackermanDistanceVector;
            odo_current=controllers_.at(i)->getOdometry();

            for (int j = 0; j < goalsAckerman_.size(); j++)
            {
                if (controllers_.at(i)->checkOriginToDestination(odo_current, goalsAckerman_.at(j), current_distance_to_goal, time_, estimated_goal_pose))
                {
                    odo_current = estimated_goal_pose;
                    ackerman_distance += current_distance_to_goal;
                    ackermanDistanceVector.push_back(current_distance_to_goal);
                    ackerman_time += time_;
                }
                else if (controllers_.at(i)->checkOriginToDestination(odo_current, goalsAckerman_.at(j), current_distance_to_goal, time_, estimated_goal_pose))
                {
                    std::cout << "Ackermann Goal Being Deleted" << std::endl; // THIS SHOULD NEVER HAPPEN COS QUADCOPTER SHOULD ACCEPT ANY GOAL
                    goalsAckerman_.erase(goalsAckerman_.begin() + j);         // DELETE
                }
            }
        }
    }
}

bool Mission::run()
{
    for (unsigned int i = 0; i < controllers_.size(); i++)
    {
        if (controllers_.at(i)->getPlatformType() == pfms::PlatformType::QUADCOPTER)
        {
            controllers_.at(i)->setGoals(goals_quadcopter_);
            controllers_.at(i)->run();
        }
        else if (controllers_.at(i)->getPlatformType() == pfms::PlatformType::ACKERMAN)
        {
            controllers_.at(i)->setGoals(goalsAckerman_);
            controllers_.at(i)->run();
        }
    }
    return true;
}

std::vector<unsigned int> Mission::status()
//  Retrurns mission completion status (indicating percentage of completion of task) by each platform @sa setGoals
//   @return vector with each element of vector corresponding to a platform. The value is percent of completed distance
// of entire mission for the corresponding platform value between 0-100.
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::vector<unsigned int> returnStatus;
    for (auto object : controllers_) 
    {
        double percentage = 0;

        if (object->getPlatformType() == pfms::PlatformType::QUADCOPTER)
        {
            percentage = (object->distanceTravelled() / quadcopter_distance) * 100;
            if (percentage > 100 && object->status() == pfms::PlatformStatus::IDLE)
            {percentage = 100;}
            else if (percentage > 99 && !(object->status() == pfms::PlatformStatus::IDLE))
            {percentage = 99;}
            else if (percentage > 20 && object->status() == pfms::PlatformStatus::IDLE) // Because status lags behind, i gotta make it 100%
            { percentage = 100;}
            std::cout << "QUADCOPTER STATUS " << percentage << " %" << std::endl;
            std::cout << "QUADCOPTER DISTANCE " << quadcopter_distance << std::endl;
            std::cout << "QUADCOPTER DISTANCE Travelled" << object->distanceTravelled() << std::endl<<std::endl;
        }

        else if (object->getPlatformType() == pfms::PlatformType::ACKERMAN)
        {
            percentage = (object->distanceTravelled() / ackerman_distance) * 100;
            if (percentage > 100 && object->status() == pfms::PlatformStatus::IDLE)
            {percentage = 100;}
            else if (percentage > 99 && !(object->status() == pfms::PlatformStatus::IDLE))
            {percentage = 99;}
            else if (percentage > 20 && object->status() == pfms::PlatformStatus::IDLE) // Because status lags behind, i gotta make it 100%
            {percentage = 100;}

            std::cout << " ACKERMAN STATUS " << percentage << " %" << std::endl;
            std::cout << " ACKERMAN DISTANCE " << ackerman_distance << std::endl;
            std::cout << "ACKERMAN DISTANCE TRAVELLED" << object->distanceTravelled()  << std::endl<<std::endl;
        }
        // before i push_back, round up
        unsigned int temp = ceil(percentage);
        returnStatus.push_back(temp);
    }
    return returnStatus;
}

void Mission::setMissionObjective(mission::Objective objective)
{objective_ = objective;}

// Pushing back the distance travelled
std::vector<double> Mission::getDistanceTravelled()
{
    std::vector<double> get_distance_travelled_vector;

    for (int i = 0; i < controllers_.size(); i++)
    {get_distance_travelled_vector.push_back(controllers_.at(i)->distanceTravelled());}
    return get_distance_travelled_vector;
}

// Pushing back the elapsed time
std::vector<double> Mission::getTimeMoving()
{
    std::vector<double> get_time_moving_vector;

    for (int i = 0; i < controllers_.size(); i++)
    {get_time_moving_vector.push_back(controllers_.at(i)->timeTravelled());}
    return get_time_moving_vector;
}

std::vector<std::pair<int, int>> Mission::getPlatformGoalAssociation()
{
    std::vector<std::pair<int, int>> get_platform_association_vector;
    std::pair<int, int> pushPair;
    int quadcopter_goal_number = 0;
    int ackerman_goal_number = 0;
    float distancex = 0;
    float distancey = 0;

    if (platform_ == pfms::PlatformType::ACKERMAN)
    {
        pushPair.first = pfms::PlatformType::ACKERMAN;
        for (int i = 0; i < goals_.size(); i++)
        {
            bool check = false;
            while (check)
            {
                int j = 0;
                distancex = goals_.at(i).x - goals_quadcopter_.at(j).x;
                distancey = goals_.at(i).y - goals_quadcopter_.at(j).y;

                if ((distancex + distancey) < 0.1)
                {
                    pushPair.second = j;
                    check = true;
                }
                j++;
            }
            get_platform_association_vector.push_back(pushPair);
        }
    }
    else if (platform_ == pfms::PlatformType::QUADCOPTER)
    {
        pushPair.first = pfms::PlatformType::QUADCOPTER;
        for (int i = 0; i < goals_.size(); i++)
        {
            bool check = false;
            while (check)
            {
                int j = 0;
                distancex = goals_.at(i).x - goalsAckerman_.at(j).x;
                distancey = goals_.at(i).y - goalsAckerman_.at(j).y;

                if ((distancex + distancey) < 0.1)
                {
                    pushPair.second = j;
                    check = true;
                }
                j++;
            }
            get_platform_association_vector.push_back(pushPair);
        }
    }

    return get_platform_association_vector;
}