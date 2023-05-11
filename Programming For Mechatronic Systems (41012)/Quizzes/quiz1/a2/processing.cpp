#include "processing.h"

void removeLargerThanArea(std::vector<Shape *> &shapes, double limit)
{
    int capacity = shapes.capacity();

    for (int i = 0; i < capacity; i++)
    {
        double area = (*shapes.at(i)).getArea();
        if (area > limit)
        {
            shapes.erase(shapes.begin() + i);
            i--;
            capacity--;
        }
    }
}
