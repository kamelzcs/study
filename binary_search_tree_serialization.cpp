/*
 * binary_search_tree_serialization.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>
#include<fstream>
#include<string>
#include<iostream>
#include<limits>
#include<queue>
using namespace std;

int INT_MAX = std::numeric_limits<int>::max();
int INT_MIN = std::numeric_limits<int>::min();

typedef struct ListNode ListNode;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

typedef struct TreeNode TreeNode;
struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode(): left(NULL), right(NULL){}
    TreeNode(int data): val(data), left(NULL), right(NULL){}
}*root;

void readBST(int min, int max, int &insertVal, TreeNode *&pos, ifstream &fin){
    if( insertVal > min && insertVal < max){
        int val = insertVal;
        pos = new TreeNode(val);
        if(fin >> insertVal){
            readBST(min, val, insertVal, pos->left, fin);
            readBST(val, max, insertVal, pos->right, fin);
        }
    }
}

void readBST(TreeNode *&pos, ifstream &fin){
    string val;
    fin >> val;
    if( val == "#") return;
    int data = stoi(val);
    pos = new TreeNode(data);
    readBST(pos->left, fin);
    readBST(pos->right, fin);
}

void traverse(TreeNode *root){
    if(root){
        traverse(root->left);
        printf("%d\n", root->val);
        traverse(root->right);
    }
}

int maxHeight(TreeNode *pos){
    if( pos == NULL) return 0;
    return max(maxHeight(pos->left), maxHeight(pos->right)) + 1;
}

void printLevel(TreeNode *pos, int level){
    if ( pos == NULL) return;
    if(level == 0) {
        cout << pos->val << " ";
        return;
    }
    printLevel(pos->left, level - 1);
    printLevel(pos->right, level -1);
}

void DfsPrintLevelOrder(TreeNode *pos){
    int height = maxHeight(pos);
    for(int i=0; i<height; ++i){
        printLevel(pos, i);
        cout << endl;
    }
}

void BfsPrintLevelOrder(TreeNode *pos){
    queue<TreeNode *> nodesQueue;
    int currentLevel = 0,  nextLevel = 0;
    nodesQueue.push(pos);
    currentLevel = 1;
    while(!nodesQueue.empty()){
        TreeNode *top = nodesQueue.front();
        cout << top->val << " ";
        nodesQueue.pop();
        if(top->left) {
            nodesQueue.push(top->left);
            nextLevel++;
        }
        if(top->right){
            nodesQueue.push(top->right);
            nextLevel++;
        }
        if((--currentLevel) == 0){
            cout << endl;
            currentLevel = nextLevel;
            nextLevel = 0;
        }
    }
}

TreeNode *sortedArrayToBST(vector<int> &num, int left, int right){
    if(left >= right) return NULL;
    int middle = left + (right - left)/2;
    TreeNode *node = new TreeNode(num[middle]);
    node->left = sortedArrayToBST(num, left, middle);
    node->right = sortedArrayToBST(num, middle+1, right);
    return node;
}

TreeNode *sortedArrayToBST(vector<int> &num) {
    int len = num.size();
    return sortedArrayToBST(num, 0, len);
}

int getListLen(ListNode *head){
    int ans = 0;
    while(head){
        ans++;
        head = head->next;
    }
    return ans;
}

TreeNode *sortedListToBST(ListNode *&head, int start, int end) {
    if(start >= end) return NULL;
    int middle = start + (end - start)/2;
    TreeNode *leftChild = sortedListToBST(head, start, middle);
    TreeNode *current = new TreeNode(head->val);
    head = head->next;
    current->left = leftChild;
    current->right = sortedListToBST(head, middle + 1, end);
    return current;
}

TreeNode *sortedListToBST(ListNode *head) {
    int len = getListLen(head);
    TreeNode *node = sortedListToBST(head, 0, len);
    return node;
}

int main(int argc, char *argv[])
{
    //ifstream fin("test");
    //readBST(root, fin);
    //traverse(root);
    //BfsPrintLevelOrder(root);
    vector<int> v{1,2,4,5};
    BfsPrintLevelOrder(sortedArrayToBST(v));
    return 0;
}


