/*
 * repeated_dna.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<algorithm>
#include<iostream>
#include<memory.h>
using namespace std;

#define SIZE 19880101
char hashed[SIZE];

class Solution {
public:
    int transform(char x){
        switch(x){
            case 'A':
                return 0;
            case 'C':
                return 1;
            case 'G':
                return 2;
            case 'T':
                return 3;
        }
    }

    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        memset(hashed, 0, sizeof(hashed));
        int len = s.size();
        if(len < 10){
            return ans;
        }
        int current = 0;
        for(int i = 0; i < 10; ++i){
            current = (current * 4 + transform(s[i]) % SIZE);
        }
        hashed[current] = 1;
        for(int i = 10; i < len; ++i){
            current = ((((current - (transform(s[i - 10]) * (1 << 18))) % SIZE) + SIZE) * 4 + transform(s[i])) % SIZE;
            if(hashed[current]){
                if(hashed[current] == 1){
                    cout << s.substr(i - 9, 10) << endl;
                    ans.push_back(s.substr(i - 9, 10));
                    hashed[current] = 2;
                }
            }
            else{
                hashed[current] = 1;
            }
        }
        return ans;
    }
};

int main(){
    //vector<string> ans = (new Solution())->findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    vector<string> ans = (new Solution())->findRepeatedDnaSequences("AAAAAAAAAAAAAAAA");
    return 0;
}
