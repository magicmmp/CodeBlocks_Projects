/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
/*ţ������Ŀ���Ѷ���������ת��Ϊ˫������*/
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        TreeNode* pre_node=NULL;/*�ϴα����ʵĽڵ�*/
        TreeNode* first=NULL; /*����ĵ�һ��Ԫ�أ�ָ��ֵ�������ʼ������ֵ�ǲ�ȷ����*/
        visit(pRootOfTree,pre_node,first);

        return first;
    }
    /*�ݹ飬�������*/
    void visit(TreeNode* cur,TreeNode* &pre_node,TreeNode* &first)
    {
        if(cur==NULL)
            return;
        /*���ʵ�ǰ�ڵ��������*/
        visit(cur->left,pre_node,first);
        /*���ʵ�ǰ�ڵ�*/
        if(pre_node)
            pre_node->right=cur;
        else
            first=cur; /*û��ǰ���Ľڵ㣬��������ĵ�һ���ڵ�*/
        cur->left=pre_node;
        pre_node=cur;
        /*���ʵ�ǰ�ڵ��������*/
        visit(cur->right,pre_node,first);

    }
};
