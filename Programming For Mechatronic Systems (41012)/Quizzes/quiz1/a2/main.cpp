#include <iostream>
#include "rectangle.h"
#include "processing.h"
#include <vector>

int main()
{
    //! TODO: Create a rectangle
    Rectangle rectangle1;
    rectangle1.setHeightWidth(5.0, 3.55);

    // Print some info about it
    std::cout << "The area of "
              << "rectangle1"
              << " is " << rectangle1.getArea() << std::endl;
    std::cout << "It is a: " << rectangle1.getDescription() << std::endl;

    Rectangle rectangle2(6, 7);
    Rectangle rectangle3(1, 7);
    Rectangle rectangle4(0.1, 7);
    Rectangle rectangle5(90, 7);

    std::vector<Shape*> shape{&rectangle2 ,&rectangle3, &rectangle4, &rectangle5};
    removeLargerThanArea(shape, 20);
    std::cout<<shape.size()<<std::endl<<std::endl;
}
