/*
 * linked_list.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>
struct list_node{
    int data;
    list_node *prev, *next;
    list_node(){prev = next = this;}
    list_node(int content):prev(this),next(this){
        this->data = content;
    }
}head;

void init_list_head(struct list_node *head){
    head->prev = head;
    head->next = head;
}

bool list_empty(struct list_node *head){
    return head->next == head;
}

bool list_last(struct list_node *node, struct list_node *head){
    return node->next == head;
}

/* insert new_node between prev and next
 *
 */
void list_node_add(struct list_node *new_node, struct list_node *prev, struct list_node *next){
    new_node->next = next;
    next->prev = new_node;
    prev->next = new_node;
    new_node->prev = prev;
}

/* prepend the node before following node.
 *
 */
void list_node_prepend(struct list_node *new_node, struct list_node *following){
    list_node_add(new_node, following->prev, following);
}

void list_node_append(struct list_node *new_node, struct list_node *prev_node){
    list_node_add(new_node, prev_node, prev_node->next);
}

void list_node_traverse(struct list_node *head){
    struct list_node *pos = head->next;
    while(pos != head){
        printf("%d ", pos->data);
        pos = pos->next;
    }
    putchar('\n');
}

void list_node_remove(struct list_node *node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

int main(int argc, char *argv[])
{
    struct list_node first = list_node(1), second = list_node(2), third = list_node(3);
    list_node_prepend(&first, &head);
    list_node_prepend(&second, &first);
    list_node_append(&third, &second);
    list_node_traverse(&head);
    list_node_remove(&second);
    list_node_traverse(&head);
    return 0;
}


