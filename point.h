#ifndef PUNKT_H_INCLUDED
#define PUNKT_H_INCLUDED


template <typename Type>
class Point
{
    public:
        Type x;
        Type y;
        Point()
        {
        };
        Point(Type pointX,Type pointY);
        Type get_x(void) const;
        Type get_y(void) const;
        void set_x(Type xToSet);
        void set_y(Type yToSet);

};

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

#endif // PUNKT_H_INCLUDED
