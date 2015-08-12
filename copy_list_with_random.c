#include<stdlib.h>
struct RandomListNode {
 int label;
 struct RandomListNode *next;
 struct RandomListNode *random;
};

void appendNew(struct RandomListNode* head){
    if(!head){
        return;
    }
    struct RandomListNode* current = (struct RandomListNode*)malloc(sizeof(struct RandomListNode));
    struct RandomListNode* head_nxt = head->next;
    current->label = head->label;
    current->next = head_nxt;
    current->random = NULL;
    head->next = current;
    appendNew(head_nxt);
}

void setRandom(struct RandomListNode* head){
    if(!head){
        return;
    }
    if(head->random){
        head->next->random = head->random->next;
    }
    setRandom(head->next->next);
}

void restore(struct RandomListNode* head){
    if(!head){
        return;
    }
    struct RandomListNode* head_nxt = head->next->next, *copy = head->next;
    head->next = head_nxt;
    if(head_nxt){
        copy->next = head_nxt->next;
    }
    else{
        copy->next = NULL;
    }
    restore(head_nxt);
}

struct RandomListNode *copyRandomList(struct RandomListNode *head) {
    if(!head){
        return head;
    }
    appendNew(head);
    setRandom(head);
    struct RandomListNode* ans = head->next;
    restore(head);
    return ans;
}
