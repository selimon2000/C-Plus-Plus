#include "rectangle.h"

//    TASK 2
//    The `Rectangle` class already has a special member function.
//    Thanks to *Polymorphism* we can have functions with same name but different number of parameters.
//    Can you add to the `Rectangle` class another function that enables the `Rectangle` to on creation have `width` , `height`
//    and `description` initialised with values supplied by user of the class.
//    You will need to add the declaration of this member function in the [header of Rectangle class](./a2/rectangle.h) as
//    well as implement this function in [implementation file of Rectangle class](./a2/rectangle.cpp).


Rectangle::Rectangle():
width_(0.0), height_(0.0)
{
    description_="square";
}

Rectangle::Rectangle(double width, double height):width_(width), height_(height)
{
    setHeightWidth( width, height);
}

void Rectangle::setHeightWidth(double width, double height)
{
    // This is a example of why you should not allow direct access to member variables (why they are private)
    // Given we have a function to set the member varaibles, we also can leverage this function to set any
    // other member variables required, of perform any other operations that are needed to be executed
    // (such as invoking other methods)
    width_ = width;
    height_ = height;
    double tolerance=0.01;

    if (abs(width_- height_)<=tolerance) { //PROBING Q - Is this the best way to do floating point comparsion????
        description_ = "square";
    } else {
        description_ = "rectangle";
    }
}

double Rectangle::getArea()
{
    return width_ * height_;
}

// std::string Rectangle::getDescription()
// {
//     return description_;
// }
