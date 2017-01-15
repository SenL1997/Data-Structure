#ifndef SEQLIST_H_INCLUDED
#define SEQLIST_H_INCLUDED

#include <iostream>

using namespace std;
template<class elemType>
class list
{
    public:
    virtual void create(int i)=0;
    virtual void clear()=0;
    virtual int length() const = 0;
    virtual void insert(int i, const elemType &x)=0;
    virtual void remove(int i)=0;
    virtual int search(const elemType &x) const = 0;
    virtual elemType visit(int i) const = 0;
    virtual void traverse() const = 0;
    virtual void reverse() = 0;
    virtual ~list(){};
};


template<class elemType>
class seqList:public list<elemType>
{
    private:
    elemType *data;
    int currentLength;
    int maxSize;

    void doubleSpace();
    public:
        void create(int initSize = 10);
        ~seqList(){delete[] data;}
        void clear(){currentLength = 0;}
        int length() const{return currentLength;}
        void insert(int i, const elemType &x);
        void remove(int i);
        int search(const elemType &x) const;
        elemType visit(int i)const;
        void traverse() const;
        void reverse();
};

class OutOfBound{};
class IllegalSize{};

#endif // SEQLIST_H_INCLUDED
