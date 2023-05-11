#include "rangeprocessing.h"
#include <algorithm>
#include <numeric>

namespace range_processing
{
    //! @todo
    //! TASK 1 - Refer to README.md and the Header file for full description
    bool detectHeightOfObject(sensor_msgs::Range rangeScan, geometry_msgs::Pose pose, double &height)
    {
        if ((rangeScan.range >= rangeScan.min_range) && (rangeScan.range < rangeScan.max_range))
        {
            height = pose.position.z - rangeScan.range;
            return true;
        }

        return false;
    }

    //! @todo
    //! TASK 2 - Refer to README.md and the Header file for full description
    bool detectPerson(sensor_msgs::Range rangeScan, geometry_msgs::Pose pose, double personHeight, geometry_msgs::Point &location)
    {
        if ((rangeScan.range >= rangeScan.min_range) && (rangeScan.range < rangeScan.max_range))
        {
            if (fabs(pose.position.z - rangeScan.range - personHeight) < 0.1)
            {
                location.x = pose.position.x;
                location.y = pose.position.y;
                location.z = pose.position.z - rangeScan.range;

                return true;
            }
        }

        return false;
    }
}