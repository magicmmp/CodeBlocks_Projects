/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
/*牛客网题目，把二叉搜索树转换为双向链表*/
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        TreeNode* pre_node=NULL;/*上次被访问的节点*/
        TreeNode* first=NULL; /*链表的第一个元素，指针值如果不初始化，则值是不确定的*/
        visit(pRootOfTree,pre_node,first);

        return first;
    }
    /*递归，中序遍历*/
    void visit(TreeNode* cur,TreeNode* &pre_node,TreeNode* &first)
    {
        if(cur==NULL)
            return;
        /*访问当前节点的左子树*/
        visit(cur->left,pre_node,first);
        /*访问当前节点*/
        if(pre_node)
            pre_node->right=cur;
        else
            first=cur; /*没有前驱的节点，是新链表的第一个节点*/
        cur->left=pre_node;
        pre_node=cur;
        /*访问当前节点的右子树*/
        visit(cur->right,pre_node,first);

    }
};
