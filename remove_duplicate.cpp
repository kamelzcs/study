/*
 * remove_duplicate.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if( head == NULL) return head;
        ListNode **current = &head;
        while(*current) {
            bool is_duplicate = false;
            ListNode **next_node = &(*current)->next;
            while(*next_node) {
                if( (*next_node)->val == (*current)->val){
                    (*next_node) = (*next_node)->next;
                    is_duplicate = true;
                }
                else{
                    next_node = &(*next_node)->next;
                }
            }
            if(is_duplicate){
                (*current) = (*current)->next;
            }
            else{
                current = &(*current)->next;
            }
        }
        return head;

    }
};


