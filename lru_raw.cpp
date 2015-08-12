/*
 * lru_raw.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<list>
#include<algorithm>
#include<unordered_map>
using namespace std;

class LRUCache{
public:
    LRUCache(int capacity):left(capacity) {
    }

    int get(int key) {
    }

    void set(int key, int value) {
    }

private:
    int left;
    void update(HPIL::iterator it){
    }
};

class DoubleLinkedListNode{
    public:
        DoubleLinkedListNode(){
            data = -1;
            pre = next = this;
        }
        DoubleLinkedListNode(int d): data(d){
            pre = next = this;
        }
        ~DoubleLinkedListNode(){
        }
        void deleteMyself(){
            pre->next = this->next;
            delete this;
        }
        void append(DoubleLinkedListNode* node){
            node->next = this->next;
            node->pre = this;
        }
        int data;
        DoubleLinkedListNode *pre, *next;
};

class DoubleLinkedList{
    public:
        DoubleLinkedList(){
            head = new DoubleLinkedListNode();
        }
        void deleteNode(DoubleLinkedListNode *node){
            node->deleteMyself();
        }
        void addFirst(int data){
            DoubleLinkedListNode *node = new DoubleLinkedListNode(data);
            head->append(node);
        }
    private:
        DoubleLinkedListNode *head;
};


