/*
 * remote_nth_node.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
struct ListNode {
 int val;
 ListNode *next;
 ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode **pre = &head, *ahead = head;
        while(n){
            ahead = ahead->next;
            n--;
        }
        while(ahead){
            ahead = ahead->next;
            pre = &(*pre)->next;
        }
        (*pre) = (*pre)->next;
        return head;
    }

    ListNode *swapPairs(ListNode *head) {
        ListNode **current = &head, *cached = head, *next = NULL, *next_next = NULL;
        while ((*current) && (*current)->next){
            cached = (*current);
            next = (*current)->next;
            next_next = next->next;
            (*current) = next;
            next->next = cached;
            cached->next = next_next;
            current = &cached->next;
        }
        return head;
    }
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        ListNode **pre_head = &head;
        int current_index = 1;
        while(current_index <= m - 1){
            pre_head = &(*pre_head)->next;
            current_index++;
        }

        ListNode *internal_tail = (*pre_head);
        ListNode *internal_head = internal_tail->next;
        ListNode *temp_head = internal_tail;
        current_index++;
        // reverse the next interval [m,n]
        while (current_index <= n){
            ListNode *next = internal_head->next;
            internal_head->next = temp_head;
            temp_head = internal_head;
            internal_head = next;
            current_index++;
        }
        (*pre_head)->next = temp_head;
        internal_tail->next = internal_head;
        return head;
    }

    ListNode *partition(ListNode *head, int x){
        ListNode *smaller_tail = NULL, *bigger_tail = NULL, *bigger_head = NULL, *smaller_head = NULL;
        while(head){
         if(head->val < x){
             if(smaller_head == NULL){
                 smaller_head = smaller_tail = head;
             }
             else{
                 smaller_tail->next = head;
                 smaller_tail = smaller_tail->next;
             }
         }
         else{
             if(bigger_head == NULL){
                 bigger_head = bigger_tail = head;
             }
             else{
                 bigger_tail->next = head;
                 bigger_tail = bigger_tail->next;
             }
         }
         head = head->next;
        }
        if(bigger_tail !=NULL){
         bigger_tail->next = NULL;
        }
        if(smaller_tail){
            smaller_tail->next = bigger_head;
            return smaller_head;
        }
        else{
            return bigger_head;
        }
    }
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(k == 1) return head;
        ListNode **current = &head, *next = head;
        int remain_length = k;
        while(1){
            while(next && remain_length){
                next = next->next;
                remain_length--;
            }
            if(remain_length > 0){
                return head;
            }
            else
            {
                // remove from (*current) to next
                ListNode *temp_head = (*current), *temp_next = temp_head->next;
                while(temp_next !=next){
                    ListNode *cached_temp_next_next = temp_next->next;
                    temp_next->next = temp_head;
                    temp_head = temp_next;
                    temp_next = cached_temp_next_next;
                }
                (*current)->next = next;
                ListNode **cached_current = &(*current)->next;
                (*current) = temp_head;
                current = cached_current;
                remain_length = k;
            }
        }
        return head;
    }

    void flatten(TreeNode *root) {
        if(root == NULL) return;
        if(root->left == NULL){
            flatten(root->right);
        }
        else{
            TreeNode *right_most = root->left;
            while(right_most->right) right_most = right_most->right;
            flatten(root->left);
            if(root->right !=NULL){
                flatten(root->right);
                right_most->right = root->right;
            }
            root->right = root->left;
            root->left = NULL;
        }
    }
};



