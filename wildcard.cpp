/*
 * wildmatch.c
 * Copyright (C) 2015 zhao <zhao@kamel-ThinkPad-X201>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>
#include<string.h>
#include <stdbool.h>

bool dp[2][100000];
int len_s, len_p;

int count(char *p){
    int ans = 0;
    while(*p){
        if(*(p++) == '*'){
            ans++;
        }
    }
    return ans;
}

bool isMatch(char *s, char *p){
    len_s = strlen(s);
    len_p = strlen(p);
    int count_star = count(p);
    if(len_p - count_star > len_s){
        return false;
    }
    int i, j;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;
    for(i = 1; i <= len_p; ++i){
        for(j = 0; j <= len_s; ++ j){
            if(!j){
                dp[i%2][j] = dp[(i + 1)%2][j] && (p[i - 1] == '*');
            }
            else{
                if(p[i - 1] == '?'){
                    dp[i % 2][j] = dp[(i + 1) % 2][j - 1];
                }
                else if(p[i - 1] == '*'){
                    // zero
                    dp[i % 2][j] = dp[i % 2][j - 1];
                    //one
                    dp[i % 2][j] |= dp[(i + 1) % 2][j - 1];
                    //more
                    dp[i % 2][j] |= dp[(i + 1) % 2][j];
                }
                else{
                    dp[i % 2][j] = dp[(i + 1) % 2][j - 1] && (s[j - 1] == p[i - 1]);
                }
            }
        }
    }
    return dp[len_p % 2][len_s];
}

int main(){
    char s1[] = "";
    char s2[] = "*";
    printf("%d\n", isMatch(s1, s2));
}

