/*
 * longestPali.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


#include<algorithm>
#include<memory.h>
#include<string>
using namespace std;

class Solution {
public:
    int dp[1000][1000];
    string longestPalindrome(string s) {
        if(s == ""){
            return s;
        }
        memset(dp, 0, sizeof(dp));
        int len_s = s.size();
        for(int i = 0; i < len_s; ++i){
            dp[i][i] = true;
        }
        int ans_start = 0, ans_len = 1;
        for(int l = 2; l <= len_s; ++l){
            for(int start = 0; start + l <= len_s; ++start){
                int end = start + l - 1;
                if(s[start] != s[end]){
                    continue;
                }
                if(l > 2){
                    dp[start][end] = dp[start + 1][end - 1];
                }
                else{
                    dp[start][end] = true;
                }
                if(dp[start][end]){
                    ans_start = start;
                    ans_len = l;
                }
            }
        }
        return s.substr(ans_start, ans_len);
    }
};

