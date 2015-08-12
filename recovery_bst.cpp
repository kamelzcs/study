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
    void recoverTree(TreeNode* root) {
        TreeNode *pre = new TreeNode(-100000);
        TreeNode *stack[1000];
        int top = 0;
        TreeNode *first = NULL, *second = NULL, *current=root;
        while(top || current){
            if(current){
                stack[top++] = current;
                current = current->left;
            }
            else{
                current = stack[--top];
                if(current->val < pre->val){
                    if(!first){
                        first = pre;
                        second = current;
                    }
                    else{
                        second = current;
                        break;
                    }
                }
                pre = current;
                current = current->right;
            }
        }
        swap(first->val, second->val);
    }
};


