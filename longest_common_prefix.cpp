/*
 * longest_common_prefix.cpp
 * Copyright (C) 2014 zhao
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<iostream>
#include<map>
using namespace std;
struct Node{
    int count;
    map<char, struct Node*> children;
    Node(): count(0){}
    Node* insert(char value){
        Node *next;
        if(children.count(value) == 0){
            next = new Node();
            children[value] = next;
        }
        else{
            next = children[value];
        }
        next->count++;
        return next;
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        Node *root = new Node();
        for(vector<string>::iterator it = strs.begin(); it != strs.end(); ++it){
            Node *current = root;
            for(int i = 0; i < (int)(*it).size(); ++i){
                current = current->insert((*it)[i]);
            }
        }
        string ans = "";
        Node *current = root;
        while(true){
            bool valid = false;
            for(map<char, struct Node*> ::iterator it = current->children.begin(); it != current->children.end(); ++it){
                if(it->second->count == strs.size()){
                    ans += it->first;
                    valid = true;
                    current = it->second;
                    break;
                }
            }
            if(valid == false){
                return ans;
            }
        }
        return ans;
    }
};

int main(int argc, char *argv[])
{
    Solution *t = new Solution();
    string a = "ABC", b = "";
    vector<string> vs;
    vs.push_back(a);
    vs.push_back(b);
    cout<< t->longestCommonPrefix(vs) << endl;
    return 0;
}
