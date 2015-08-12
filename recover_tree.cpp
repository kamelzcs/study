/*
 * recover_tree.cpp
 * Copyright (C) 2014 zhao
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<algorithm>
using namespace std;

struct TreeNode {
 int val;
 TreeNode *left;
 TreeNode *right;
 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#define INF 0x7f7f7f7f
class Solution {
public:
    bool check(TreeNode *root, int left, int right){
        if(root == NULL){
            return true;
        }
        if(root->val < left || root->val > right){
            return false;
        }
        return check(root->left, left, min(right, root->val)) && check(root->right, max(left, root->val), right);
    }
    void value_swap(TreeNode *first, TreeNode *second){
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
    TreeNode* find_maximum(TreeNode *root){
        TreeNode* ans = root;
        if(root->left){
            TreeNode* temp = find_maximum(root->left);
            if(temp->val > ans->val){
                ans = temp;
            }
        }
        if(root->right){
            TreeNode* temp = find_maximum(root->right);
            if(temp->val > ans->val){
                ans = temp;
            }
        }
        return ans;
    }
    TreeNode* find_minimum(TreeNode *root){
        TreeNode* ans = root;
        if(root->left){
            TreeNode* temp = find_minimum(root->left);
            if(temp->val < ans->val){
                ans = temp;
            }
        }
        if(root->right){
            TreeNode* temp = find_minimum(root->right);
            if(temp->val < ans->val){
                ans = temp;
            }
        }
        return ans;
    }
    void recover_left_right(TreeNode *root){
        TreeNode *minimum = find_minimum(root->right);
        TreeNode *maxminum = find_maximum(root->left);
        value_swap(minimum, maxminum);
    }
    void recoverTree(TreeNode *root) {
        if(root == NULL){
            return;
        }
        bool left_valid = true, right_valid = true;
        if(root->left){
            left_valid = check(root->left, -INF, root->val);
        }
        if(root->right){
            right_valid = check(root->right, root->val, INF);
        }
        if(left_valid == false && right_valid == false){
            recover_left_right(root);
        }
        else{
            if(left_valid){
                TreeNode *minimum = find_minimum(root->right);
                if(minimum->val >= root->val){
                    recoverTree(root->right);
                }
                else{
                    value_swap(root, minimum);
                }
            }
            else{
                TreeNode *maxminum = find_maximum(root->left);
                if(maxminum->val <= root->val){
                    recoverTree(root->left);
                }
                else{
                    value_swap(root, maxminum);
                }
            }
        }
    }
};

