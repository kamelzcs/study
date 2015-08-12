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
    bool hasCycle(ListNode *head) {
        if(head == NULL) return false;
        if(head->next == NULL) return false;
        ListNode *fast = head, *slow = head;
        do{
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) return true;
        }while(slow !=NULL && fast!=NULL && fast->next!=NULL);
        return false;
    }
};


