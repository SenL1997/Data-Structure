#include "seqList.h"
template <class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = data;
    maxSize*=2;
    data=new elemType[maxSize];

    for (int i =0;i<currentLength;++i)
        data[i]=tmp[i];
    delete[] tmp;
}

template <class elemType>
void seqList<elemType>::create(int initSize)
{
    if (initSize<=0) throw IllegalSize();
    data=new elemType[initSize];
    maxSize=initSize;
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x)
{
    if (i<0||i>currentLength)throw OutOfBound();
    if(currentLength == maxSize) doubleSpace();
    for (int j=currentLength;j>i;j--)data[j]=data[j-1];
    data[i]=x;
    ++currentLength;
}

template<class elemType>
void seqList<elemType>::remove(int i)
{
    if (i<0||i>currentLength-1) throw OutOfBound();
    for (int j=i;j<currentLength-1;j++) data[j]=data[j+1];
    --currentLength;
}

template<class elemType>
int seqList<elemType>::search(const elemType &x) const
{
    int i=0;
    for (i=0;i<currentLength&&data[i].no!=x.no;++i);//结构体中搜索No.因为学号唯一
    if(i==currentLength)return -1;else return i;
}

template<class elemType>
elemType seqList<elemType>::visit(int i)const
{
    if(i<0||i>currentLength-1)throw OutOfBound();
    return data[i];
}

template<class elemType>
void seqList<elemType>::traverse()const
{
    cout << endl;
    for (int i=0;i<currentLength;++i)
    {
        cout << "No: "<<data[i].no<<" name: "<<data[i].name<<" birthday: "<<data[i].birthday.month<<"/";
        cout << data[i].birthday.day<<"/"<<data[i].birthday.year<<" score: "<<data[i].score<<endl;
    }
}

template<class elemType>
void seqList<elemType>::reverse()
{
    cout <<endl;
    for (int i=0;i<currentLength/2;++i)
    {
        elemType tmp;
        tmp = data[i];
        data[i]=data[currentLength-1-i];
        data[currentLength-1-i]=tmp;
    }
        //cout << data[i]<<' ';
}
