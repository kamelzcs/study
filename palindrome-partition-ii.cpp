/*
 * palindrome-partition-ii.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<string>
#include<iostream>
#include<memory.h>
using namespace std;
#define size 1500
int isPali[size][size];
int dp[size];
class Solution {
public:
    string str;
    int len;
    int minCut(string s) {
        str=s;
        len=str.size();
        memset(isPali, 0, sizeof(isPali));
        for(int i=0; i<len; ++i){
            isPali[i][0]=isPali[i][1]=1;
        }
        for(int l=2; l<=len; ++l){
            for(int i = 0; i + l <= len; ++i){
                if(str[i] != str[i + l - 1]) continue;
                else isPali[i][l] = isPali[i + 1][l - 2];
            }
        }

        memset(dp, 0x1f, sizeof(dp));
        dp[0]=0;
        for(int i = 1; i < len; ++i){
            if(isPali[0][i + 1]){
                 dp[i]=0;
            }
            else
            {
                for(int j = i; j > 0; --j){
                    if(isPali[j][i - j + 1]){
                        dp[i] = min (dp[i], dp[j - 1] + 1);
                    }
                }
            }
        }
        return dp[len - 1];
    }
};

int main(int argc, char *argv[])
{
    Solution *t = new Solution();
    cout<< t->minCut("leet");
    return 0;
}



