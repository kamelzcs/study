/*
 * sort_list_2.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


#include<stdio.h>
#include<memory.h>

struct ListNode {
 int val;
 ListNode *next;
 ListNode(int x) : val(x), next(NULL) {}
};

int max(int a, int b){
    return a > b ? a : b;
}

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if(!l2){
            return l1;
        }
        if(!l1){
            return l2;
        }
        if(l1->val < l2->val){
            ListNode *nxt = mergeTwoLists(l1->next, l2);
            l1->next = nxt;
            return l1;
        }
        else{
            ListNode *nxt = mergeTwoLists(l1, l2->next);
            l2->next = nxt;
            return l2;
        }
    }
    ListNode *sortList(ListNode *head) {
        if(head == NULL) return NULL;
        ListNode *part[30];
        memset(part, 0, sizeof(part));
        int max_pos = 0;
        ListNode *cur_node = head;
        while(cur_node){
            ListNode *nxt_node = cur_node->next;
            int pos = 0;
            cur_node->next = NULL;
            ListNode *cur_list = cur_node;
            for(; part[pos]; ++pos){
                cur_list = mergeTwoLists(cur_list, part[pos]);
                part[pos] = NULL;
            }
            part[pos] = cur_list;
            max_pos = max(pos, max_pos);
            cur_node = nxt_node;
        }
        ListNode *ans = NULL;
        for(int i = 0; i <= max_pos; ++i){
            if(part[i]){
                ans = mergeTwoLists(ans, part[i]);
            }
        }
        return ans;
    }
};
