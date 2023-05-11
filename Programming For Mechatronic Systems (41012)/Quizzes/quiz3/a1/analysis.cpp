#include "analysis.h"
#include "tf.h"
#include "tf2.h"
#include <iostream>
#include <utility>
#include <functional>

using geometry_msgs::Point;
using std::pair;
using std::vector;

Analysis::Analysis(std::vector<Point> goals) : goals_(goals)
{
}

//! @todo
//! TASK 3 - Refer to README.md and the Header file for full description
vector<double> Analysis::timeToImpact(Pose origin)
{
    // The consts you will need are
    // Display::OMEGA_MAX
    // Display::V_MAX

    vector<double> times;

    for (int i = 0; i < goals_.size(); i++)
    {
        double xDistance = goals_.at(i).x - origin.position.x;
        double yDistance = goals_.at(i).y - origin.position.y;
        double range = hypot(xDistance, yDistance);

        double enemyBearing = atan2(yDistance, xDistance);
        double originYaw = tf::quaternionToYaw(origin.orientation);
        double headingAngle = tf2::normaliseAngle(enemyBearing - originYaw);

        double linearTime = range / Display::V_MAX;
        double angularTime = std::fabs(headingAngle / Display::OMEGA_MAX);
        double totalTime = linearTime + angularTime;

        times.push_back(totalTime);
    }

    return times;
}

//! @todo
//! TASK 4 - Refer to README.md and the Header file for full description
AdjacencyList Analysis::exportGraph()
{
    vector<EdgeInfo> edge;

    // std::make_pair(odom.at(i), i));
    AdjacencyList graph;

    unsigned int i = 0;
    double xDistance = goals_.at(i).x;
    double yDistance = goals_.at(i).y;
    double range = hypot(xDistance, yDistance);

    edge.push_back(std::make_pair(range, i));

    for (; i < goals_.size(); i++)
    {
        double xDistance = goals_.at(i).x - goals_.at(i - 1).x;
        double yDistance = goals_.at(i).y - goals_.at(i - 1).y;
        double range = hypot(xDistance, yDistance);

        edge.push_back(std::make_pair(range, i));
    }

    graph.push_back(edge);

    return graph;
}