/*
 * binary_search_tree.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stack>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
    stack<TreeNode *> stk;
public:
    BSTIterator(TreeNode *root) {
      TreeNode* current = root;
      while(current){
        stk.push(current);
        current = current->left;
      }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
      return !stk.empty();
    }

    /** @return the next smallest number */
    int next() {
      TreeNode* top = stk.top();
      stk.pop();
      TreeNode* current = top->right;
      while(current){
        stk.push(current);
        current = current->left;
      }
      return top->val;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
