/*
 * merge_k_lists.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


#include<stdio.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
struct ListNode {
 int val;
 ListNode *next;
 ListNode(int x) : val(x), next(NULL) {}
};
struct CompareNode{
    bool operator()(const ListNode *p1, const ListNode *p2){
        return p1->val < p2->val;
    }
};
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        priority_queue<ListNode*, vector<ListNode*>, CompareNode> q;
        for(vector<ListNode *>::iterator itr = lists.begin(); itr != lists.end(); itr++){
            if(*itr){
                q.push(*itr);
            }
        }

        ListNode *head = new ListNode(0);
        ListNode *tail = head;
        while(!q.empty()){
            ListNode *top = q.top();
            tail->next = top;
            tail = tail->next;
            q.pop();
            if(top->next){
                q.push(top->next);
            }
        }
        tail->next = NULL;
        return head->next;
    }
};
int main(int argc, char *argv[])
{
    
    return 0;
}


