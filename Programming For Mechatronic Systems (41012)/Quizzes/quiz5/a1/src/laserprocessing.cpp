#include "laserprocessing.h"
#include <algorithm>
#include <numeric>

using namespace std;

LaserProcessing::LaserProcessing(sensor_msgs::LaserScan laserScan) : laserScan_(laserScan)
{
}

//! @todo
//! TASK 1 - Refer to README.md and the Header file for full description
unsigned int LaserProcessing::countObjectReadings()
{
    unsigned int count = 0;

    for (auto i : laserScan_.ranges)
    {
        if ((i >= 0) && (i < laserScan_.range_max))
        {
            count++;
        }
    }

    return count;
}

//! @todo
//! TASK 2 - Refer to README.md and the Header file for full description
unsigned int LaserProcessing::countSegments()
{
    unsigned int count = 0;
    unsigned int oldLocation = 1000;

    for (int i = 1; i < laserScan_.ranges.size(); i++)
    {
        bool withinRange = true;

        if (laserScan_.ranges.at(i) >= 0 && laserScan_.ranges.at(i) < laserScan_.range_max && laserScan_.ranges.at(i - 1) >= 0 && laserScan_.ranges.at(i - 1) < laserScan_.range_max)
        {
            double deltaX = laserScan_.ranges.at(i) * cos(laserScan_.angle_min + laserScan_.angle_increment * i) - laserScan_.ranges.at(i - 1) * cos(laserScan_.angle_min + laserScan_.angle_increment * (i - 1));
            double deltaY = laserScan_.ranges.at(i) * sin(laserScan_.angle_min + laserScan_.angle_increment * i) - laserScan_.ranges.at(i - 1) * sin(laserScan_.angle_min + laserScan_.angle_increment * (i - 1));
            double distance = std::hypot(deltaX, deltaY);

            if (distance < 0.3)
            {
                if (oldLocation != i - 1)
                {
                    count++;
                }
                oldLocation = i;
            }
        }
    }

    ROS_INFO_STREAM("SEGMENT COUNT: " << count);
    return count;
}

//! @todo
//! TASK 3 - Refer to README.md and the Header file for full description
geometry_msgs::Point LaserProcessing::detectClosestCone()
{
    unsigned int oldLocation = 1000;
    vector<pair<int, int>> startFinishLocations;
    pair<int, int> pushPair;

    bool started = false;

    for (int i = 1; i < laserScan_.ranges.size(); i++)
    {
        bool withinRange = true;

        if (laserScan_.ranges.at(i) >= 0 && laserScan_.ranges.at(i) < laserScan_.range_max && laserScan_.ranges.at(i - 1) >= 0 && laserScan_.ranges.at(i - 1) < laserScan_.range_max)
        {
            double deltaX = laserScan_.ranges.at(i) * cos(laserScan_.angle_min + laserScan_.angle_increment * i) - laserScan_.ranges.at(i - 1) * cos(laserScan_.angle_min + laserScan_.angle_increment * (i - 1));
            double deltaY = laserScan_.ranges.at(i) * sin(laserScan_.angle_min + laserScan_.angle_increment * i) - laserScan_.ranges.at(i - 1) * sin(laserScan_.angle_min + laserScan_.angle_increment * (i - 1));
            double distance = std::hypot(deltaX, deltaY);

            if (distance < 0.3)
            {
                if (oldLocation != i - 1)
                {
                    if (started)
                    {
                        startFinishLocations.push_back(pushPair);
                    }

                    pushPair.first = i;
                    pushPair.second = i;
                    oldLocation = i;
                }
                else
                {
                    oldLocation = i;
                    pushPair.second = i;
                    started = true;
                }
            }
        }
    }
    // if it's the end of the vector, and we started a new push pair (front), and we haven't pushed back, then we check if we should push or not
    if (startFinishLocations.back() != pushPair)
    {
        startFinishLocations.push_back(pushPair);
    }

    // For Printing out the above
    /*
    cout << "Size of startFinishLocations Vector: " << startFinishLocations.size() << endl;
    for (int i = 0; i < startFinishLocations.size(); i++)
    {
        cout << "At startFinishLocation [" << i << "], fist element is: " << startFinishLocations.at(i).first << ", second element is: " << startFinishLocations.at(i).second << endl;
    }
    */

    double distance = 0;
    double smallestDistance = 100000;
    geometry_msgs::Point returnPoint;
    geometry_msgs::Point tempPoint;

    for (int i = 0; i < startFinishLocations.size(); i++)
    {
        double distanceX = 0;
        double distanceY = 0;

        for (int j = startFinishLocations.at(i).first; j <= startFinishLocations.at(i).second; j++)
        {
            tempPoint = polarToCart(j);
            distanceX += tempPoint.x;
            distanceY += tempPoint.y;
        }

        tempPoint.x = distanceX / ((startFinishLocations.at(i).second - startFinishLocations.at(i).first) + 1);
        tempPoint.y = distanceY / ((startFinishLocations.at(i).second - startFinishLocations.at(i).first) + 1);
        distance = std::hypot(tempPoint.x, tempPoint.y);

        if (distance < smallestDistance)
        {
            smallestDistance = distance;
            returnPoint = tempPoint;
        }
    }

    return returnPoint;
}

//! @todo
//! TASK 4 - Refer to README.md and the Header file for full description
geometry_msgs::Point LaserProcessing::detectRoadCentre()
{
    unsigned int oldLocation = 1000;
    vector<pair<int, int>> startFinishLocations;
    pair<int, int> pushPair;

    bool started = false;

    for (int i = 1; i < laserScan_.ranges.size(); i++)
    {
        bool withinRange = true;

        if (laserScan_.ranges.at(i) >= 0 && laserScan_.ranges.at(i) < laserScan_.range_max && laserScan_.ranges.at(i - 1) >= 0 && laserScan_.ranges.at(i - 1) < laserScan_.range_max)
        {
            double deltaX = laserScan_.ranges.at(i) * cos(laserScan_.angle_min + laserScan_.angle_increment * i) - laserScan_.ranges.at(i - 1) * cos(laserScan_.angle_min + laserScan_.angle_increment * (i - 1));
            double deltaY = laserScan_.ranges.at(i) * sin(laserScan_.angle_min + laserScan_.angle_increment * i) - laserScan_.ranges.at(i - 1) * sin(laserScan_.angle_min + laserScan_.angle_increment * (i - 1));
            double distance = std::hypot(deltaX, deltaY);

            if (distance < 0.3)
            {
                if (oldLocation != i - 1)
                {
                    if (started)
                    {
                        startFinishLocations.push_back(pushPair);
                    }

                    pushPair.first = i;
                    pushPair.second = i;
                    oldLocation = i;
                }
                else
                {
                    oldLocation = i;
                    pushPair.second = i;
                    started = true;
                }
            }
        }
    }
    // if it's the end of the vector, and we started a new push pair (front), and we haven't pushed back, then we check if we should push or not
    if (startFinishLocations.back() != pushPair)
    {
        startFinishLocations.push_back(pushPair);
    }

    double distance = 0;
    double smallestDistance = 100000;
    double secondSmallestDistance = 100000;

    geometry_msgs::Point closestPoint, secondClosestPoint;
    geometry_msgs::Point tempPoint;

    for (int i = 0; i < startFinishLocations.size(); i++)
    {
        double distanceX = 0;
        double distanceY = 0;

        for (int j = startFinishLocations.at(i).first; j <= startFinishLocations.at(i).second; j++)
        {
            tempPoint = polarToCart(j);
            distanceX += tempPoint.x;
            distanceY += tempPoint.y;
        }

        tempPoint.x = distanceX / ((startFinishLocations.at(i).second - startFinishLocations.at(i).first) + 1);
        tempPoint.y = distanceY / ((startFinishLocations.at(i).second - startFinishLocations.at(i).first) + 1);
        distance = std::hypot(tempPoint.x, tempPoint.y);

        if (distance < smallestDistance)
        {
            secondSmallestDistance = smallestDistance;
            smallestDistance = distance;
            secondClosestPoint=closestPoint;
            closestPoint = tempPoint;
        }
        else if (distance < secondSmallestDistance)
        {
            secondSmallestDistance = distance;
            secondClosestPoint = tempPoint;
        }
    }

    geometry_msgs::Point centrepoint;
    centrepoint.x = (closestPoint.x + secondClosestPoint.x) / 2;
    centrepoint.y = (closestPoint.y + secondClosestPoint.y) / 2;
    cout<<"Centrepoint: "<<centrepoint.x<<","<<centrepoint.y<<endl;
    return centrepoint;
}

void LaserProcessing::newScan(sensor_msgs::LaserScan laserScan)
{
    laserScan_ = laserScan;
}

geometry_msgs::Point LaserProcessing::polarToCart(unsigned int index)
{
    float angle = laserScan_.angle_min + laserScan_.angle_increment * index; // + angle_range/2;
    float range = laserScan_.ranges.at(index);
    geometry_msgs::Point cart;
    cart.x = static_cast<double>(range * cos(angle));
    cart.y = static_cast<double>(range * sin(angle));
    return cart;
}

double LaserProcessing::angleConnectingPoints(geometry_msgs::Point p1, geometry_msgs::Point p2)
{
    return atan2(p2.y - p1.y, p2.x - p1.x);
}
