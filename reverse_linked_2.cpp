/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverse(struct ListNode* head, int delta){
    if(delta == 1){
        return head;
    }
    struct ListNode* nxt = head->next;
    struct ListNode* new_head = reverse(nxt, delta - 1);
    struct ListNode* new_tail = nxt->next;
    head->next = new_tail;
    nxt->next = head;
    return new_head;
}
struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
    if(!head){
        return head;
    }
    int delta = n - m + 1;
    if(m == 1){
        return reverse(head, delta);
    }
    struct ListNode* current = head;
    while(m > 2){
        current = current->next;
        m--;
    }
    struct ListNode* middle_head = reverse(current->next, delta);
    current->next = middle_head;
    return head;
}
