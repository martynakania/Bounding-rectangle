#include <iostream>
#include "point.h"

//namespace Projekt;
template <typename Type>
Point<Type>::Point(Type pointX, Type pointY)
    {
        x=pointX;
        y=pointY;
    }

template <typename Type>
Type Point<Type>::get_x() const
{
    return x;
}

template <typename Type>
Type Point<Type>::get_y() const
{
    return y;
}

template <typename Type>
void Point<Type>::set_x(Type xToSet)
{
    x=xToSet;
}

template <typename Type>
void Point<Type>::set_y(Type yToSet)
{
    y=yToSet;
}

