/*
 * suffix_tree_2.cpp
 * Copyright (C) 2014 zhao <zhao@kamel-ThinkPad-X201>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<algorithm>
#include<map>
#include<memory.h>
#include<assert.h>
#define SIZE 100010
#define ALPHA 26
int *e;
int last_non;
int *dummy;

typedef struct node node;
struct node{
    int start;
    int *end;
    int leaf_index;
    node* suffix_link, *parent;
    std::map<char, node*>child;
    node(){
    }
    node(int s, int *t, node* back, node* p, int sindex){
        start = s;
        end = t;
        suffix_link = back;
        parent = p;
        leaf_index = sindex;
    }
    node(const node& clone):start(clone.start), end(clone.end), suffix_link(clone.suffix_link), leaf_index(clone.leaf_index), parent(clone.parent){
    }
};

node *pre, *root, *parent, *current;
char str[SIZE];
int len, remain_len;

void init(){
    e = new int(0);
    dummy = new int(-1);
    root = new node(-1, dummy, NULL, NULL, -1);
}

int edge_len(node* now){
    return *now->end - now->start + 1;
}

int walk_down(node** now, int remain){
    int length = edge_len(*now);
    while( (*now)->leaf_index < 0 && length <= remain){
        remain -= length;
        (*now) = (*now)->child[str[*(*now)->end + 1]];
    }
    return remain;
}

void build(){
    //build s[0]
    node *first = new node(0, e, NULL, root, 0);
    root->child[str[0]] = first;
    current = first;
    last_non = 0;
    remain_len = 1;
    pre = NULL;
    //build phase s[i + 1] from s[i]
    for(int i = 0; i < len - 1; ++i){
        //implicity do extensions to s[0, last_non]
        *e = i + 1;
        //build s[j + 1, i + 1] from s[j, i]
        //current is the last node(s[j, i] for consitency)
        //for the s[last_non + 1, i + 1], current is the s[ last_non, i]
        current = root->child[str[last_non]];
        remain_len = walk_down(&current, i - last_non + 1);
        printf("last_non remain_len %d %d\n", last_non, remain_len);
        for(int j = last_non + 1; j <= i + 1; ++j){
            printf("current->leaf_index %d\n", current->leaf_index);
            if(current->leaf_index < 0){ // at the internal node
                    current = current->suffix_link;
            }
            else{
                current = current->parent;
                printf("current is root %d\n", current == root);
                if(current != root){
                    remain_len = remain_len + edge_len(current);
                    current = current->suffix_link;
                }
                else{
                    current = root->child[str[j]];
                    remain_len--;
                }
            }
            printf("origin remain_len %d\n", remain_len);
            remain_len = walk_down(&current, remain_len);
            printf("after remain_len %d\n", remain_len);
            if(pre != NULL){
                if(current->leaf_index >= 0){ //now at a leaf
                    pre->suffix_link = current->parent;
                }
                else{
                    pre->suffix_link = current;
                }
            }
            if(edge_len(current) == remain_len){ //rule 1
                puts("rule 1");
                current->end = e;
                last_non = j;
                pre = NULL;
                current->leaf_index = j;
            }
            else{
                if( str[current->start + remain_len] == str[i + 1]){ //rule 3
                    puts("rule 3");
                    last_non = j - 1;
                    pre = NULL;
                    break;
                }
                else{ //rule 2
                    puts("rule 2");
                    parent = current->parent;
                    int* middle_end = new int(current->start + remain_len - 1);
                    printf("middle_end, remain_len %d %d\n", *middle_end, remain_len);
                    node* middle = new node(current->start, middle_end, NULL, parent, -1);
                    parent->child[str[current->start]] = middle;
                    current->start = (*middle_end) + 1;
                    middle->child[str[current->start]] = current;
                    node *new_leaf = new node(i + 1, e, NULL, middle, j);
                    middle->child[str[i + 1]] = new_leaf;
                    if(pre != NULL){
                        pre->suffix_link = middle;
                    }
                    pre = middle;
                    current = middle->parent;
                    remain_len = edge_len(middle) + edge_len(current);
                    last_non = j;
                }
            }
            //else{ //at the leaf node
                //parent = current->parent;
                //remain_len = remain_len + edge_len(parent);
                //if(parent != NULL){
                    //current = parent->suffix_link;
                    //remain_len = walk_down(&current, remain_len);
                //}
            //}
        }
    }
}

void print(node* now){
    printf("%d %d %d\n", now->start, *now->end, now->leaf_index);
    for(std::map<char, node*>::iterator itr = now->child.begin(); itr != now->child.end(); ++itr){
        printf("%c\n", itr->first);
        print(itr->second);
    }
}

int main(){
    scanf("%s", str);
    len = strlen(str);
    init();
    build();
    puts("print tree-----------");
    print(root);
    return 0;
}
