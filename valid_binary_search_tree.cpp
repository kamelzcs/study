/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode *current = root;
        TreeNode *stack[2000];
        int top = 0;
        bool first = true;
        int pre = -2147483648;
        while(current || top){
            if(current){
                stack[top++] = current;
                current = current->left;
            }
            else{
                current = stack[--top];
                if(!first && current->val <= pre){
                    return false;
                }
                pre = current->val;
                current = current->right;
                first = false;
            }
        }
        return true;
    }
};


