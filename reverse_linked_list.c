/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverse(struct ListNode *root, int len){
    if(len == 1){
        return root;
    }
    struct ListNode *cur_tail = root->next;
    struct ListNode *head = reverse(root->next, len - 1);
    root->next = cur_tail->next;
    cur_tail->next = root;
    return head;
}
struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* current = dummy;
    dummy->next = head;
    int len = n - m + 1;
    int remain = m;
    while(remain > 1){
        current = current->next;
        remain--;
    }
    current->next = reverse(current->next, len);
    return dummy->next;
}


