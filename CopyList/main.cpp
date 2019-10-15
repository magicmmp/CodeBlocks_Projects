#include <iostream>

using namespace std;

struct node
{
    int val;
    node*next;
    node(int v):val(v),next(nullptr){}
};

int main()
{
    node* p1;
    node* h1;
    h1=new node(10);
    p1=h1;
    for(int i=9;i>0;i--)
    {
        p1->next=new node(i);
        p1=p1->next;
    }
    p1=h1;
    cout<<"List 1:"<<endl;
    while(p1)
    {
        cout<<' '<<p1->val;
        p1=p1->next;
    }
    cout<<endl;
    node *p2;
    node *h2;
    p1=h1;
    h2=new node(p1->val);
    p2=h2;
    while(p1->next)
    {
        p1=p1->next;
        p2->next=new node(p1->val);
        p2=p2->next;
    }
    cout<<"List 2:"<<endl;
    p2=h2;
    while(p2)
    {
        cout<<' '<<p2->val;
        p2=p2->next;
    }
    cout<<endl;








    return 0;
}
