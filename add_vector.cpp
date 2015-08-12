/*
 * add_vector.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<functional>
#include<vector>
#include<iostream>

struct node{
    std::vector<int> data;
    node(char *s){
        int len = strlen(s);
        for(int i = 0; i < len; ++i){
            data.push_back(s[len - 1 - i] - '0');
        }
    }
    node(){
    }
    node(std::vector<int>d): data(d) {
    }
    node(const node &n): data(n.data){
    }
    node& operator=(node n){
        swap(n);
        return *this;
    }
    ~node(){
        data.clear();
    }
    node add(node &b){
        node ans;
        int len = std::max(this->data.size(), b.data.size());
        int carry = 0;

        for(int i = 0; i < len; ++i){
            int p0 = 0, p1 = 0;
            if(i < this->data.size()){
                p0 = this->data[i];
            }
            if(i < b.data.size()){
                p1 = b.data[i];
            }
            int total = p0 + p1 + carry;
            carry = total / 10;
            ans.data.push_back(total % 10);
        }
        if(carry){
            ans.data.push_back(carry);
        }
        return ans;
    }
    void swap(node& rhs){
        std::swap(data, rhs.data);
    }
    void output(){
        for(int i = 0; i < this->data.size(); ++i){
            printf("%d", this->data[this->data.size() - 1 - i]);
        }
        printf("\n");
    }
};



int main(){
    char a[100], b[100];
    scanf("%s%s", a, b);
    node left(a), right(b);
    node ans = left.add(right);
    ans.output();
    return 0;
}


