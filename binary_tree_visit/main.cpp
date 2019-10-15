#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/**
* @brief 后序遍历，非递归.
*/
void post_order(const binary_tree_node_t *root, int (*visit)(const binary_tree_node_t*))
{
     /* p，正在访问的结点， q，刚刚访问过的结点 */
    const binary_tree_node_t *p, *q;
    stack<const binary_tree_node_t *> s;
    p = root;
   do
   {
     while(p != NULL)
     { /* 往左下走 */
       s.push(p);
       p = p->left;
     }
     q = NULL;
     while(!s.empty())
     {
       p = s.top();
       s.pop();
       /* 右孩子不存在或已被访问，访问之 */
       if(p->right == q)
       {
         visit(p);
         q = p; /* 保存刚访问过的结点 */
       }
       else
       {
        /* 当前结点不能访问，需第二次进栈 */
         s.push(p);
        /* 先处理右子树 */
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
