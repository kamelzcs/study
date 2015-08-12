/*
 * unique_path.c
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>

int dp[200][200];
int C(int n, int a){
    a = a < n - a ? a: n - a;
    if(a == 0){
        return 1;
    }
    int ret = dp[n][a];
    if(ret >= 0){
        return ret;
    }
    return dp[n][n - a] = dp[n][a] = C(n - 1, a) + C(n - 1, a - 1);
}

int uniquePaths(int m, int n) {
    memset(dp, 0xff, sizeof(dp));
    return C(m + n - 2, n - 1);
}

int main(){
    printf("%d\n", uniquePaths(100, 3));
    printf("%d\n", uniquePaths(1, 100));
    return 0;
}


