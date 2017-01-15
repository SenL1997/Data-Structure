#include "linkedList.h"

template <class elemType>
void linkedList<elemType>::clear()
{
	while(length()>0) remove(0);
}

template <class elemType>
void linkedList<elemType>::insert(int i, const elemType &x)
{
    node *p = get(i-1);
    p->next=new node(x,p->next);
    ++size;
}

template <class elemType>
void linkedList<elemType>::remove(int i)
{
    node *p=get(i-1);
    node *q=p->next;
    p->next = q->next;
    delete q;
    --size;
}
template <class elemType>
int linkedList<elemType>::search(const elemType &x) const
{
    node *p = head -> next;
    for (int i=0;p;++i)
    {
        if(x.no==p->value.no)return i;//每位同学学号唯一，故只搜索学号
        p=p->next;
    }
    return -1;
}

template <class elemType>
elemType linkedList<elemType>::visit(int i)const
{
    return get(i)->value;
}

template <class elemType>
void linkedList<elemType>::traverse()const
{
    node *p=head->next;
    while(p)
    {
        cout << "No: "<<p->value.no<<" name: "<<p->value.name<<" birthday: "<<p->value.birthday.month<<"/";
        cout << p->value.birthday.day<<"/"<<p->value.birthday.year<<" score: "<<p->value.score<<endl;
        p=p->next;
    }
}

template <class elemType>
void linkedList<elemType>::reverse()
{
    if (head->next==NULL) return;

    node *cur=head->next->next;
    node *cur_next;

    head->next->next=NULL;
    while(cur!=NULL)
    {
        cur_next=cur->next;
        cur->next=head->next;
        head->next=cur;
        cur=cur_next;
    }
}



