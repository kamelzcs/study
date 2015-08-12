struct ListNode {
 int val;
 struct ListNode *next;
};

#define NULL 0

void twist(struct ListNode* first, struct ListNode* second){
    if(!first){
        return;
    }
    struct ListNode* nxt_first = first->next;
    first->next = second;
    if(!second){
        return;
    }
    struct ListNode* nxt_second = second->next;
    second->next = nxt_first;
    twist(nxt_first, nxt_second);
}

struct ListNode* reverse(struct ListNode *head){
    if(!head->next){
        return head;
    }
    struct ListNode* ans = reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return ans;
}

struct ListNode* middleEnd(struct ListNode* head){
    struct ListNode* fast = head, *slow = head;
    while(1){
        if(!fast->next || !fast->next->next){
            return slow;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
}

void reorderList(struct ListNode* head) {
    if(!head || !head->next){
        return;
    }
    struct ListNode* first_end = middleEnd(head);
    struct ListNode* second_start = first_end->next;
    first_end->next = NULL;
    second_start = reverse(second_start);
    twist(head, second_start);
}
