/*
 * merge_sorted_list.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
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

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        ListNode *head = new ListNode(0);
        ListNode *temp = head;
        while( l1 && l2){
            if(l1->val < l2->val){
                head->next = l1;
                l1 = l1->next;
            }
            else{
                head->next = l2;
                l2 = l2->next;
            }
            head = head->next;
        }
        if(l1) head->next = l1;
        else head->next = l2;
        return temp->next;
    }
    ListNode *sortList(ListNode *head) {
        if(head == NULL) return NULL;
        ListNode *part[30];
        memset(part, 0, sizeof(part));
        ListNode *list, *current;
        list = head;
        int max_len = 0;
        while(list){
            current = list;
            list = list->next;
            current->next = NULL;
            int pos;
            for(pos = 0; part[pos]; ++pos){
                current = mergeTwoLists(current, part[pos]);
                part[pos] = NULL;
            }
            part[pos] = current;
            if(pos > max_len) max_len = pos;
        }
        for(int pos = 0; pos <= max_len; ++pos){
            if(part[pos]) list = mergeTwoLists(list, part[pos]);
        }
        return list;
    }
};
