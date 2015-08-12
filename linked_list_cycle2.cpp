/*
 * linked_list_cycle.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head == NULL) return NULL;
        if(head->next == NULL) return NULL;
        ListNode *fast = head, *slow = head;
        do{
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) break;
        }while(slow !=NULL && fast!=NULL && fast->next!=NULL);
        if (slow == NULL || slow!=fast) return NULL;
        ListNode *start = head;
        while(slow != start){
            slow = slow->next;
            start = start->next;
        }
        return slow;
    }
};


