 struct ListNode {
     int val;
     struct ListNode *next;
 };

#define NULL 0

struct ListNode* insertNode(struct ListNode* cur, struct ListNode* node){
    if(!cur){
        return node;
    }
    if(cur->val < node->val){
        cur->next = insertNode(cur->next, node);
        return cur;
    }
    else{
        node->next = cur;
        return node;
    }
}

struct ListNode* insertionSortList(struct ListNode* head) {
    struct ListNode* ans = NULL;
    struct ListNode *cur_node = head;
    while(cur_node){
        struct ListNode* nxt_node = cur_node->next;
        cur_node->next = NULL;
        ans = insertNode(ans, cur_node);
        cur_node = nxt_node;
    }
    return ans;
}


