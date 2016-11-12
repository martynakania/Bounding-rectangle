#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED
#include <iostream>
#include <exception>
#include <algorithm>
#include "point.h"
namespace Projekt
{
template <typename Type>
class Rectangle //ew x y szerokosc dlugosc
    {
         Point <Type>topRight;
         Point <Type>bottomLeft;
         //wspólrzedne przeciwleglych rogow rownoczesnie rownania bokow
    public:

        Rectangle(const Point<Type>& point1,const Point<Type>& point2);
        Rectangle(Type x1, Type y1, Type x2, Type y2);
        Rectangle()
                    {} ;
        Type get_width() const;
        Type get_length() const;
        Point<Type> get_left_bottom_corner() const;
        Point<Type> get_right_top_corner() const;
        Type get_x_left() const;
        Type get_x_right() const;
        Type get_y_bottom() const;
        Type get_y_top() const;
        void set_x(Type x1, Type x2);
        void set_y(Type y1, Type y2);
        bool overlap(const Rectangle& rectangleToCompare) const;
        bool operator==(const Rectangle& compareTo) const;
        bool operator!=(const Rectangle& compareTo) const;
        Rectangle<Type> operator+(Rectangle rectangleToAdd) const;
        Rectangle<Type> operator-(Rectangle rectangleToSub) const;
        Rectangle<Type>& operator+=(const Rectangle& rectangleToAdd);
        Rectangle<Type>& operator-=(const Rectangle& rectangleToSub);
        Rectangle<Type>& operator=(const Rectangle& rectangleToCopy);
        bool cointains_point(const Point<Type>&) const;
    };

template <typename Type>
std::ostream& operator<< (std::ostream &os, const Rectangle<Type> &rectangle)
{
   return os << "( (" <<rectangle.get_x_left() <<","<< rectangle.get_y_bottom() <<")("<<rectangle.get_x_right() <<","<< rectangle.get_y_top() <<") )";
}



class Error_intersection_does_not_exist: public std::exception
{
public:

    const char* what()
        {
            return "You tried to make an intersection of rectangles which do not overlap each other";
        }

};
template <typename Type>
Rectangle<Type>::Rectangle(const Point<Type>& point1,const Point<Type>& point2)
{
    if(point1.x>point2.x)
    {
        topRight.x=point1.x;
        bottomLeft.x=point2.x;
    }
    else
    {
        bottomLeft.x=point1.x;
        topRight.x=point2.x;
    }

    if (point1.y>point2.y)
    {
        bottomLeft.y=point2.y;
        topRight.y=point1.y;
    }
    else
    {
        bottomLeft.y=point1.y;
        topRight.y=point2.y;
    }
}

template <typename Type>
Rectangle<Type>::Rectangle(Type x1, Type y1, Type x2, Type y2)
{
    if (x1<x2)
    {
        bottomLeft.set_x(x1);
        topRight.set_x(x2);
    }
    else
    {
        bottomLeft.set_x(x2);
        topRight.set_x(x1);
    }

    if (y1<y2)
    {
        bottomLeft.set_y(y1);
        topRight.set_y(y2);
    }
    else
    {
        bottomLeft.set_y(y2);
        topRight.set_y(y1);
    }
}

template <typename Type>
Type Rectangle<Type>::get_width() const
{
    return topRight.get_x()-bottomLeft.get_x();
}

template <typename Type>
Type Rectangle<Type>::get_length() const
{
    return topRight.get_y()-bottomLeft.get_y();
}

template <typename Type>
Type Rectangle<Type>::get_x_left() const
{
    return bottomLeft.get_x();
}

template <typename Type>
Type Rectangle<Type>::get_x_right() const
{
    return topRight.get_x();
}

template <typename Type>
Type Rectangle<Type>::get_y_bottom() const
{
    return bottomLeft.get_y();
}

template <typename Type>
Type Rectangle<Type>::get_y_top() const
{
    return topRight.get_y();
}

template <typename Type>
Point<Type> Rectangle<Type>::get_left_bottom_corner() const
{
    return this->bottomLeft;
}

template <typename Type>
Point<Type> Rectangle<Type>::get_right_top_corner() const
{
    return this->topRight;
}

template <typename Type>
void Rectangle<Type>::set_x(Type x1, Type x2)
{
    if (x1<x2)
    {
        bottomLeft.set_x(x1);
        topRight.set_x(x2);
    }
    else
    {
        bottomLeft.set_x(x2);
        topRight.set_x(x1);
    }
}

template <typename Type>
void Rectangle<Type>::set_y(Type y1, Type y2)
{
    if (y1<y2)
    {
        bottomLeft.set_y(y1);
        topRight.set_y(y2);
    }
    else
    {
        bottomLeft.set_y(y2);
        topRight.set_y(y1);
    }
}


template <typename Type>
bool Rectangle<Type>::overlap(const Rectangle& rectangleToCompare)  const
{
    if(  (rectangleToCompare.get_x_right() >= get_x_left()) && (rectangleToCompare.get_x_left() <= get_x_right())
       &&(rectangleToCompare.get_y_bottom() <= get_y_top()) && (rectangleToCompare.get_y_top() >= get_y_bottom())  )
        return true;
    else
        return false;
}

template <typename Type>
bool Rectangle<Type>::operator==(const Rectangle& compareTo) const
{
    return (   get_x_left()==compareTo.get_x_left()    && get_y_bottom()==compareTo.get_y_bottom()
            && get_x_right()==compareTo.get_x_right()  &&  get_y_top()==compareTo.get_y_top()     );
}

template <typename Type>
bool Rectangle<Type>::operator!=(const Rectangle& compareTo) const
{
    return !( this->operator==(compareTo) );
}

template <typename Type>
Rectangle<Type> Rectangle<Type>::operator+(Rectangle rectangleToAdd) const
{
    return rectangleToAdd+=*this;
}

template <typename Type>
Rectangle<Type> Rectangle<Type>::operator-(Rectangle rectangleToSub) const
{
    return rectangleToSub-=*this;
}

template <typename Type>
Rectangle<Type>& Rectangle<Type>::operator+=(const Rectangle& rectangleToAdd)
{
    if(get_x_left()>rectangleToAdd.get_x_left())
        bottomLeft.set_x( rectangleToAdd.get_x_left() );

    if(get_x_right()<rectangleToAdd.get_x_right())
        topRight.set_x( rectangleToAdd.get_x_right() );

    if(get_y_bottom()>rectangleToAdd.get_y_bottom())
        bottomLeft.set_y( rectangleToAdd.get_y_bottom() );

    if(get_y_top()<rectangleToAdd.get_y_top())
        topRight.set_y( rectangleToAdd.get_y_top() );
    return *this;
}

template <typename Type>
Rectangle<Type>& Rectangle<Type>::operator-=(const Rectangle& rectangleToSub)
{
    if( ! this->overlap(rectangleToSub) )
        throw Error_intersection_does_not_exist();


    if( get_x_left()<rectangleToSub.get_x_left() )
        bottomLeft.set_x( rectangleToSub.get_x_left() );

    if(get_x_right()>rectangleToSub.get_x_right())
        topRight.set_x( rectangleToSub.get_x_right() );

    if(get_y_bottom()<rectangleToSub.get_y_bottom())
        bottomLeft.set_y( rectangleToSub.get_y_bottom() );

    if(get_y_top()>rectangleToSub.get_y_top())
        topRight.set_y( rectangleToSub.get_y_top() );

    return *this;
}

template <typename Type>
Rectangle<Type>& Rectangle<Type>::operator=(const Rectangle& rectangleToCopy)
{
    bottomLeft.set_x( rectangleToCopy.get_x_left() );
    bottomLeft.set_y( rectangleToCopy.get_y_bottom() );
    topRight.set_x( rectangleToCopy.get_x_right() );
    topRight.set_y( rectangleToCopy.get_y_top() );
    return *this;
}

template <typename Type>
bool Rectangle<Type>::cointains_point(const Point<Type> &point) const
{
    int x=point.get_x();
    int y=point.get_y();
    if( (get_x_left()<=x) && (get_x_right()>=x) && (get_y_bottom()<=y) && (get_y_top()>=y) )
        return true;
    else
        return false;
}

}

#endif // RECTANGLE_H_INCLUDED
