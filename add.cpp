/*
 * add.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<functional>
#include<iostream>

struct node{
    int *data;
    int len;
    node(char *s): data(new int[strlen(s)]), len(strlen(s)){
        memset(data, 0, sizeof(int) * len);
        for(int i = 0; i < len; ++i){
            data[i] = s[len - 1 - i] - '0';
        }
    }
    node(): data(new int[1]), len(0){
    }
    node(int* d, int l): data(new int[l]) {
        memcpy(this->data, d, sizeof(int)*l);
        this->len = l;
    }
    node(const node &n): data(new int[n.len]){
        len = n.len;
        memcpy(data, n.data, len * sizeof(int));
    }
    node& operator=(node n){
        swap(n);
        return *this;
    }
    ~node(){
        delete[] data;
    }
    node add(node &b){
        int len = std::max(this->len, b.len);
        int carry = 0;
        int *data = new int[len + 1];
        memset(data, 0, sizeof(int) * (len + 1));

        for(int i = 0; i < len; ++i){
            int total = this->data[i] + b.data[i] + carry;
            data[i] = total % 10;
            carry = total / 10;
        }
        if(carry){
            data[len++] = carry;
        }
        return node(data, len);
    }
    void swap(node& rhs){
        std::swap(len, rhs.len);
        std::swap(data, rhs.data);
    }
};


void output(node &a){
    for(int i = 0; i < a.len; ++i){
        printf("%d", a.data[a.len - 1 - i]);
    }
    printf("\n");
}

int main(){
    char a[100], b[100];
    scanf("%s%s", a, b);
    node left(a), right(b);
    node ans = left.add(right);
    output(ans);
    return 0;
}


