#ifndef COLLECTION_H_INCLUDED
#define COLLECTION_H_INCLUDED

#include <iostream>
#include <exception>
#include "rectangle.h"
using namespace Projekt;
using namespace std;

template <typename Type>
class Collection
{
    Rectangle<Type>* tab;
    int size;
    int last;
    int amount;

    void enlarge_collection_size(int newSize);
    void shrink_collection_size(int newSize);

public:
    Collection( int newSize, const vector<Rectangle<Type>>& vect);
    Collection( const vector<Rectangle<Type>> &vect);
    Collection(int size);
    Collection(const Collection<Type>& collectionToCopy);
    int get_size();
    int get_amount();
    int get_index_of_last();
    bool is_full();
    Rectangle<Type> get_last_rectangle();
    Rectangle<Type> get_rectangle(int index);
    Rectangle<Type> get_whole_collection();
    void change_collection_size(int newSize);
    void add_rectangle(Rectangle<Type> rectangleToAdd);
    void delete_last_rectangle();
    void delete_rectangle(int index);
    void delete_rectangle(const Rectangle<Type>& rectangleToSub);
    bool contains_rectangle(Rectangle<Type> rectangle) const;
    ~Collection();
    Collection<Type>& operator=(const Collection<Type>& collectionToCopy);

};
class error_negative_size: public std::exception
{
public:

    const char* what()
    {
        return "Size of collection have to be positive";
    }

};

template <typename Type>
Collection<Type>:: Collection(int _size)
{
    if(_size<=0)
        throw error_negative_size();
    this->size=_size;
    this->tab= new Rectangle<Type>[size];
    last=-1;
    amount=0;
}

template <typename Type>
Collection<Type>:: Collection( int _size,const vector<Rectangle<Type>> &vect)
{
    if(_size<=0)
        throw error_negative_size();
    this->size=_size;
    this->tab= new Rectangle<Type>[size];
    amount=0;
    int i;
    for(i=0; i<size && i<vect.size(); i++)
    {
        tab[i]=vect[i];
        amount++;
    }
    last=i-1;
}
template <typename Type>
Collection<Type>:: Collection(const vector<Rectangle<Type>> &vect)
{
    this->size=vect.size();
    this->tab= new Rectangle<Type>[size];
    amount=0;
    int i;
    for(i=0; i<size; i++)
    {
        tab[i]=vect[i];
        amount++;
    }
    last=i-1;
}

template <typename Type>
Collection<Type>:: Collection(const Collection<Type>& toCopy)
{
    this->size=toCopy.size;
    this->tab= new Rectangle<Type>[this->size];
    for(int i=0; i<size; i++)
    {
        this->tab[i]=toCopy.tab[i];
    }
    this->last=toCopy->last;
    this->amount=toCopy->amount;
}

template <typename Type>
int Collection<Type>:: get_amount()
{
    return this->amount;
}

template <typename Type>
int Collection<Type>:: get_size()
{
    return this->size;
}

template <typename Type>
int Collection<Type>:: get_index_of_last()
{
    return this->last;
}

template <typename Type>
bool Collection<Type>:: is_full()
{
    if(amount==size)
        return true;
    return false;
}

template <typename Type>
Rectangle<Type> Collection<Type>:: get_rectangle(int index)
{
    if(is_full())
    {
        index%=size;
    }
    else
    {
        index%=last+1;
    }
    return  tab[index];
}

template <typename Type>
Rectangle<Type> Collection<Type>:: get_last_rectangle()
{
    return  tab[last];
}

template <typename Type>
Rectangle<Type> Collection<Type>::get_whole_collection()
{
    int empty=(size-amount);
    int i=(last+1+empty)%size;
    Point<Type> bottomLeftCorner=this->tab[i].get_left_bottom_corner();
    Point<Type> topRightCorner=this->tab[i].get_right_top_corner();
    while(i<last)
    {
        i=++i%size;
        if(tab[i].get_x_left()<bottomLeftCorner.x)
            bottomLeftCorner.x=tab[i].get_x_left();
        if(tab[i].get_y_bottom()<bottomLeftCorner.y)
            bottomLeftCorner.y=tab[i].get_y_bottom();
        if(tab[i].get_x_right()>topRightCorner.x)
            topRightCorner.x=tab[i].get_x_right();
        if(tab[i].get_y_top()>topRightCorner.y)
            topRightCorner.y=tab[i].get_y_top();
    }
    return Rectangle<Type>(bottomLeftCorner, topRightCorner);
}


template <typename Type>
void Collection<Type>::change_collection_size(int newSize)
{
    if(newSize<=0)
        throw error_negative_size();
    if( newSize<size)
    {
        this->shrink_collection_size(newSize);
    }
    else if( newSize>size)
    {
        enlarge_collection_size(newSize);
    }
    return;
}

template <typename Type>
void Collection<Type>:: shrink_collection_size(int newSize)
{
    Rectangle<Type>* newTab= new Rectangle<Type>[newSize];
    int difference=(size - newSize );
    int i= (last +1+difference)%size;
    for(int j=0 ; j<newSize; j++, ++i%size)
    {
        newTab[j]= tab[i];
    }
    int empty= size - amount;
    int toDelete=difference-empty;
    if(toDelete>0);
        amount -= toDelete;
    last = amount - 1;
    delete[] tab;
    tab=newTab;
    size=newSize;
}

template <typename Type>
void Collection<Type>:: enlarge_collection_size(int newSize)
{
    Rectangle<Type>* newTab= new Rectangle<Type>[newSize];
    int empty= size - amount;
    int i=0;
    int j= (last) + empty;
    do
    {
        j=(++j)%size;
        newTab[i]=tab[j];
        i++;
    }
    while(j!= last);
    last=amount-1;
    delete[] tab;
    tab=newTab;
    size=newSize;
}


template <typename Type>
void Collection<Type>::add_rectangle(Rectangle<Type> rectangleToAdd)
{
    last=++last%size;
    tab[last]=rectangleToAdd;
    if(!is_full())
        amount++;
}

template <typename Type>
void Collection<Type>::delete_last_rectangle()
{
    if(amount==0)
        return;
    --last%size;
    amount--;
}

template <typename Type>
void Collection<Type>::delete_rectangle(int index)
{
    if(index>=size)
        return;
    for(int i=index; i!=last; )
    {
        tab[i]=tab[++i%size];
    }
    --last%size;
    amount--;
}

template <typename Type>
void Collection<Type>::delete_rectangle(const Rectangle<Type>& rectangleToSub)
{
    for(int i=0; i<size; i++)
    {
        if( rectangleToSub==this->tab[i] )
            this->delate_rectangle(i);
    }
}


template <typename Type>
Collection<Type>& Collection<Type>:: operator=(const Collection<Type>& toCopy)
{
    if(toCopy.tab==this->tab)
        return *this;
    delete[] tab;
    tab=new Rectangle<Type>[toCopy.size];
    this->size=toCopy.size;
    for(int i=0; i<size; i++)
        this->tab[i]=toCopy.tab[i];
    this->last=toCopy.last;
    this->amount=toCopy.amount;
    return *this;
}

template <typename Type>
Collection<Type>:: ~Collection()
{
    delete[] this->tab;
}

#endif // COLECTION_H_INCLUDED
