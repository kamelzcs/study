/*
 * insert_linked_list.cpp
 * Copyright (C) 2014 zhao
 *
 * Distributed under terms of the MIT license.
 */


#include<stdio.h>
#define INF 2147483647

struct ListNode {
 int val;
 ListNode *next;
 ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:

    ListNode** insert(ListNode **head, ListNode **tail, ListNode *current){
        // insert *current to ordered place
        ListNode **now = head;
        ListNode **ans = tail;
        while((*now)->val < current->val) now = &(*now)->next;
        // insert *current before now
        current->next = (*now);
        if(now == tail){
            ans = &current->next;
        }
        (*now) = current;
        return ans;
    }
    ListNode *insertionSortList(ListNode *head) {
        if(head == NULL){
            return head;
        }
        ListNode *ans = new ListNode(-INF - 1), *tail = new ListNode(INF);
        ans->next = tail;
        ListNode *current = head;
        ListNode **temp_tail = &ans->next;
        while (current != NULL){
            ListNode *cached = current->next;
            temp_tail = insert(&ans, temp_tail, current);
            current = cached;
        }
        ans = ans->next;
        (*temp_tail) = NULL;
        return ans;
    }
};

int main(){
    printf("%d\n", INF);
    return 0;
}



