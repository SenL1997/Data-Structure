#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <iostream>
using namespace std;

template<class elemType>
class myList
{
    public:
    virtual void clear()=0;
    virtual int length() const = 0;
    virtual void insert(int i, const elemType &x)=0;
    virtual void remove(int i)=0;
    virtual int search(const elemType &x) const = 0;
    virtual elemType visit(int i) const = 0;
    virtual void traverse() const = 0;
    virtual void reverse() = 0;
//    virtual bool operator==(const myList &r1) const=0;
    virtual ~myList(){};
};

template<class elemType>
class linkedList:public myList<elemType>
{
	private:
		struct node{
			elemType value;
			node * next;

			node():next(NULL){}
			node(const elemType &v, node *n=NULL):value(v),next(n){}
		};
		node *head;
		int size;

	protected:
		node *get(int i) const
		{
			if(i<0) return head;
			node *p=head->next;
			for (int j=0;j<i;++j)
				p=p->next;
			return p;
		}
	public:
        linkedList():size(0)
        {
            head = new node;
        }
        void clear();
        int length() const{return size;}
        void insert(int i, const elemType &x);
        void remove(int i);
        int search(const elemType &x) const;
        elemType visit(int i)const;
        void traverse() const;
        void reverse();
//        bool operator==(const elemType &r1) const;

		~linkedList(){
			clear();
			delete head;
		}

};
class OutOfBound{};
class IllegalSize{};

#endif // LINKEDLIST_H_INCLUDED
