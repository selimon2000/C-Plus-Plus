#ifndef SHAPE_H
#define SHAPE_H

#include <string>

/*!
 *  \ingroup   ac_shapre Shape
 *  \brief     Shape base class
 *  \details
 *  This class is the base class for all shapes.\n
 */
class Shape
{
public:
    /**
     * @brief Function that sets centre of shape
     * @param x in [m]
     * @param y in [m]
     */
    Shape();

    void setCentre(double x, double y);
    /**
     * @brief Returns description of shape
     * @return description
     */
    std::string getDescription();

    virtual ~Shape(){};
    virtual double getArea(void)=0;

//    1) TASK
//    Correct the missing access specifiers of base class [shape](./b2/shape.h) so that the implementation of the
//     [`Rectangle` constructor](./a2/rectangle.cpp) can still access the required member variable of
//     `Shape` but have it restricted to users of a `Rectangle` object.

protected:
    std::string description_;//!< description of shape

private:
    double centreX_;//!< X coordinate of centre of shape
    double centreY_;//!< Y coordinate of centre of shape

};

#endif // SHAPE_H