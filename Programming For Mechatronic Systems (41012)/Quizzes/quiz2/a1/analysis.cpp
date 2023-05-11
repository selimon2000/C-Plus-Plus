#include "analysis.h"

using std::pair;
using std::vector;

//! @todo
//! TASK 1 - We need to store cars in the Analysis class, how to do this?
Analysis::Analysis(std::vector<CarInterface *> cars) : cars_(cars), raceDisplay_(nullptr)
{
}

Analysis::Analysis(std::vector<CarInterface *> cars, std::shared_ptr<DisplayRace> raceDisplay) : cars_(cars), raceDisplay_(raceDisplay)
{
}

// ! @todo
//! TASK 1 - Refer to README.md and the Header file for full description
std::vector<unsigned int> Analysis::sortByOdometry()
{
    std::vector<unsigned int> order(cars_.size(), 0); // Creating a vector, same size as cars with all zeros
    std::vector<std::pair<double, int>> car_index_pair;

    for (int i = 0; i < cars_.size(); i++)
    {
        car_index_pair.push_back(std::make_pair(cars_.at(i)->getOdometry(), cars_.at(i)->getID()));
    }

    std::sort(car_index_pair.begin(), car_index_pair.end());
    for (int i = 0; i < cars_.size(); i++)
    {
        order.at(i) = car_index_pair.at(i).second;
    }

    return order;
}

//! TASK 2 - Refer to README.md and the Header file for full description
std::vector<unsigned int> Analysis::dragRace(double distance)
{
    std::vector<unsigned int> order;
    std::vector<double> originalOdom;
    std::vector<bool> carReached(cars_.size(), false);

    for (auto car : cars_)
    {
        originalOdom.push_back(car->getOdometry());
    }

    while (order.size() < cars_.size())
    {
        for (int i = 0; i < cars_.size(); i++)
        {
            // if (cars_.at(i)->getCurrentSpeed() < cars_.at(i)->getTopSpeed())
            // {
                cars_.at(i)->accelerate();
            // }
            // else
            // {
            //     cars_.at(i)->decelerate();
            // }

            if ((cars_.at(i)->getOdometry() - originalOdom.at(i)) > distance)
            {
                if (carReached.at(i) == false)
                {
                    order.push_back(cars_.at(i)->getID());
                    carReached.at(i) = true;
                }
            }
            // std::cout << "i: " << i << std::endl;
            // std::cout << ":distance of that car " << cars_.at(i)->getOdometry() - originalOdom.at(i) << std::endl;
            // std::cout << "Order Size:" << order.size() << std::endl<< std::endl;
        }
    }
    // for (int i = 0; i < order.size(); i++)
    // {
    //     std::cout << order.at(i) << std::endl;
    // }

    return order;
}
//! @todo
//! TASK 3 - Refer to README.md and the Header file for full description
void Analysis::stopAllCars()
{
    for (auto car : cars_)
    {
        while (car->getCurrentSpeed() > 0.001)
        {
            car->decelerate();
        }
    }
}

//! @todo
// //! TASK 4 - Refer to README.md and the Header file for full description
std::vector<unsigned int> Analysis::zeroTopZeroRace()
{
    // begin race loop (car != finish)
    // if current speed < top speed: accelerate, some_race_status_bool = true 

    // if some_race_status_bool = true: 
    // if speed > 0: decelelse
    // if speed = 0: car = finish, add car to order vector
    // if number of cars finished >= cars_ size: end race loop

    std::vector<unsigned int> order;
    std::vector<bool> carReachedTopSpeed(cars_.size(), false);
    std::vector<bool> carFinished(cars_.size(), false);

    while (order.size() < cars_.size())
    {
        for (int i = 0; i < cars_.size(); i++)
        {
            if (carReachedTopSpeed.at(i) == false)
            {
                if (cars_.at(i)->getCurrentSpeed() < cars_.at(i)->getTopSpeed())
                {
                    cars_.at(i)->accelerate();
                }
                else
                {
                    carReachedTopSpeed.at(i) = true;
                }
            }

            else
            {
                if (fabs(cars_.at(i)->getCurrentSpeed() - cars_.at(i)->getTopSpeed()) > 0.0001)
                {
                    cars_.at(i)->decelerate();
                }
                else
                {
                    if (carFinished.at(i) == false)
                    {
                        order.push_back(cars_.at(i)->getID());
                        carFinished.at(i) == false;
                    }
                }
            }
        }
    }

    return order;
}

// Demo code
void Analysis::demoRace()
{

    // This is an example of how to draw 3 cars moving
    //  accelerate 300 times
    unsigned int count = 0;

    while (count < 300)
    {
        for (auto car : cars_)
        {
            car->accelerate();
        }
        if (raceDisplay_ != nullptr)
        {
            raceDisplay_->updateDisplay();
        }
        count++;
    }

    // decelerate 600 times
    count = 0;
    while (count < 600)
    {
        for (auto car : cars_)
        {
            car->decelerate();
        }
        if (raceDisplay_ != nullptr)
        {
            raceDisplay_->updateDisplay();
        }
        count++;
    }
}