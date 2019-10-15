#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/**
* @brief ����������ǵݹ�.
*/
void post_order(const binary_tree_node_t *root, int (*visit)(const binary_tree_node_t*))
{
     /* p�����ڷ��ʵĽ�㣬 q���ոշ��ʹ��Ľ�� */
    const binary_tree_node_t *p, *q;
    stack<const binary_tree_node_t *> s;
    p = root;
   do
   {
     while(p != NULL)
     { /* �������� */
       s.push(p);
       p = p->left;
     }
     q = NULL;
     while(!s.empty())
     {
       p = s.top();
       s.pop();
       /* �Һ��Ӳ����ڻ��ѱ����ʣ�����֮ */
       if(p->right == q)
       {
         visit(p);
         q = p; /* ����շ��ʹ��Ľ�� */
       }
       else
       {
        /* ��ǰ��㲻�ܷ��ʣ���ڶ��ν�ջ */
         s.push(p);
        /* �ȴ��������� */
         p = p->right;
         break;
       }
     }
   } while(!s.empty());
}


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
