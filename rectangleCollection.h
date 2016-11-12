
#include <iostream>
#include <exception>
#include "rectangle.h"
//using namespace Projekt;

template <typename Type>
class RectanglesCollection
{
    Rectangle<Type>* collection;
    int collectionSize;
    int last;
public:
    RectanglesCollection(int sizeNumber, int n,Point<Type> tab[][2]);
    Rectangle<Type> get_rectangle(int index);
    Rectangle<Type> get_rectangle_which_cointains_the_whole_collection();
    Rectangle<Type> RectanglesCollection::change_collection_size(int sizeNumber);
    void add_rectangle(Rectangle<Type> rectangleToAdd);
    void delete_rectangle(int index);
    bool contains_rectangle(Rectangle<Type> rectangle) const

    bool operator==(const RectanglesCollection& collectionToCompare) const;
    bool operator!=(const RectanglesCollection& collectionToCompare) const;
    RectanglesCollection operator+(RectanglesCollection collectionToAdd) const;
    RectanglesCollection operator-(RectanglesCollection collectionToSub) const;
    RectanglesCollection& operator+=(const RectanglesCollection& collectionToAdd);
    RectanglesCollection& operator-=(const RectanglesCollection& collectionToSub);
    RectanglesCollection& operator=(const RectanglesCollection& collectionToCopy);
};

    RectanglesCollection operator+(RectanglesCollection rectangleToAdd) const;
    RectanglesCollection operator-(RectanglesCollection rectangleToSub) const;
    RectanglesCollection& operator+=(const RectanglesCollection& rectangleToAdd);
    RectanglesCollection& operator-=(const RectanglesCollection& rectangleToSub);

template <typename Type>
RectanglesCollection:: RectanglesCollection(int sizeNumber, int n,Point<Type> tab[][2])
{
    collectionSize=sizeNumber;
    collection= new Rectangle<Type>[sizeNumber];
    int i;
    for(i=0; i<sizeNumber && i<n; i++)
    {
        collection[i]=Rectangle<Type>(tab[i][0],tab[i][1]);
    }
    last=i;
}

template <typename Type>
Rectangle RectanglesCollection:: get_rectangle(int index)
{
    while(number>=collectionSize)
    {
        number-=collectionSize;
    }
    while(number<0)
    {
        number+=collectionSize;
    }
    return  collection[number];
}

template <typename Type>
Rectangle RectanglesCollection::get_rectangle_which_cointains_the_whole_collection()
{
    Point bottomLeftCorner=this->collection[0].get_left_bottom_corner();
    Point topRightCorner=this->collection[0].get_right_top_corner();
    for(int i=0; i<collectionSize; i++)
    {
        if(collection[i].get_x_left()<bottomLeftCorner.x)
            bottomLeftCorner.x=collection[i].get_x_left();
        if(collection[i].get_y_bottom()<bottomLeftCorner.y)
            bottomLeftCorner.y=collection[i].get_y_bottom();
        if(collection[i].get_x_right()>topRightCorner.x)
            topRightCorner.x=collection[i].get_x_right();
        if(collection[i].get_y_top()>topRightCorner.y)
            topRightCorner.y=collection[i].get_y_top();
    }
    return Rectangle(bottomLeftCorner, topRightCorner);
}

template <typename Type>
void RectanglesCollection::change_collection_size(int sizeNumber)
{

    Rectangle* newCollection= new Rectangle[sizeNumber];
    for(int i=0; i<collectionSize; i++)
    {
        newCollection[i]=collection[i];
    }
    delete collection[];
    collection=newCollection;
    collectionSize=sizeNumber;
}

template <typename Type>
void RectanglesCollection::add_rectangle(Rectangle<Type> rectangleToAdd)
{
    if(last<collectionSize)
    {
        collection[last]=rectangleToAdd;
        last++;
        return;
    }

    else
        for(int i=0; i<collectionSize-1; )
        {
            collection[i]=collectionSize[++i];
        }
    collection[collectionSize-1]=rectangleToAdd;
}

template <typename Type>
void RectanglesCollection::delete_rectangle(int index)
{
    if(index>collectionSize)
        return;
    for(int i=index; i<collectionSize-1; )
    {
        collection[i]=collectionSize[++i];
    }
    delete collection[collectionSize-1];
    last--;
}

template <typename Type>
bool RectanglesCollection<Type>:: contains_rectangle(Rectangle<Type> rectangle) const
{
    for(int i=0; i<collectionSize; i++)
    {
        if(collection[i]==rectangle)
            return true;
    }
    return false;
}

template <typename Type>
bool RectanglesCollection<Type>:: operator==(const RectanglesCollection& collectionToCompare) const
{
    if(this->collectionSize!=collectionToCompare.collectionSize)
        return false;
    for(int i=0; i<collectionSize; i++)
    {
        if( !collectionToCompare.contains_rectangle(collection[i]) )
            return false;
    }
    return true;
}

template <typename Type>
bool RectanglesCollection<Type>::operator!=(const RectanglesCollection& collectionToCompare) const
{
    return !( this->operator==(collectionToCompare) );
}

template <typename Type>
RectanglesCollection<Type>& RectanglesCollection<Type>:: operator+=(const RectanglesCollection& collectionToAdd);
{
    for(int i=0; i<collectionToAdd.collectionSize; i++)
    {
        if( !this->collection.contains_rectangle(collectionToAdd[i]) )
            this->add_rectangle(Rectangle<Type> rectangleToAdd)
    }
    return *this;
}

template <typename Type>
RectanglesCollection<Type>& RectanglesCollection<Type>:: operator+(Rectangle collectionToAdd) const
{
    return rectangleToSub+=*this;
}

template <typename Type>
RectanglesCollection<Type>& RectanglesCollection<Type>:: operator-=(const RectanglesCollection& collectionToSub);
{
    for(int i=0; i<this->collectionSize; i++)
    {
        if( this->collectionToSub.contains_rectangle(collection[i])
            this->delete_rectangle(i);
    }
    return *this;
}

template <typename Type>
RectanglesCollection<Type>& RectanglesCollection<Type>:: operator-(Rectangle collectionToSub) const
{
    return rectangleToSub+=*this;
}
