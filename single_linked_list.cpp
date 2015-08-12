/*
 * single_linked_list.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>
struct llist_node{
    int data;
    llist_node *next;
    llist_node(){}
    llist_node(int value): next(NULL){
        this->data = value;
    }
};
struct llist_head{
    llist_node *first;
    llist_head(): first(NULL){}
}head;

bool llist_empty(struct llist_head *head){
    return head->first == NULL;
}

void llist_add(struct llist_head *head, struct llist_node *new_first){
    new_first->next = head->first;
    head->first = new_first;
}

void llist_traverse(struct llist_head *head){
    struct llist_node *pos = head->first;
    while(pos != NULL){
        printf("%d\n", pos->data);
        pos = pos->next;
    }
}

void llist_reverse(struct llist_head *head){
    struct llist_node *new_first = new llist_node(), *pos = head->first;
    while(pos != NULL){
        struct llist_node *tmp = pos->next;
        pos->next = new_first;
        new_first = pos;
        pos = tmp;
    }
    head->first = new_first;
}

int main(){
    struct llist_node first = llist_node(1), second = llist_node(2);
    llist_add(&head, &first);
    llist_add(&head, &second);
    llist_traverse(&head);
    llist_reverse(&head);
    llist_traverse(&head);
    return 0;
}


