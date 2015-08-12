/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *rotateRight(struct ListNode *head, int k) {
    if(!head){
        return head;
    }
    int len = 0;
    struct ListNode *temp = head;
    while(temp){
        len++;
        temp = temp->next;
    }
    k %= len;
    if(!k){
        return head;
    }
    struct ListNode *new_head = head, *ahead = head, *tail = head, *behind_tail = head;
    while(k){
        ahead = ahead->next;
        k--;
    }
    while(ahead){
        tail = ahead;
        ahead = ahead->next;
        behind_tail = new_head;
        new_head = new_head->next;
    }
    tail->next = head;
    behind_tail->next = 0;
    return new_head;
}


