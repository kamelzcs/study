/*
 * best_time_stock.c
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


#include<stdio.h>
#include<memory.h>

int dp[1000][2];

int max(int a, int b){
    return a > b? a:b;
}

int min(int a, int b){
    return a < b? a:b;
}

int bestProfit(int prices[], int n){
    int ans = 0;
    int i;
    for(i = 1; i < n; ++i){
        if(prices[i] > prices[i - 1]){
            ans += prices[i] - prices[i - 1];
        }
    }
    return ans;
}

int maxProfit(int k, int prices[], int n) {
    if(k >= n / 2){
        return bestProfit(prices, n);
    }
    memset(dp, 0, sizeof(dp));
    int i, tran;
    for(tran = 1; tran <= k; ++tran){
        int temp = -prices[0];
        for(i = 1; i <= n; ++i){
            dp[i][tran % 2] = max(dp[i][(tran + 1) % 2], max(dp[i - 1][tran % 2], prices[i - 1] + temp));
            temp = max(temp, dp[i][(tran + 1) % 2] - prices[i - 1]);
        }
    }
    return dp[n][k % 2];
}

int main(){
    int prices[] = {1, 2, 3, 1, 4};
    printf("%d\n", maxProfit(3, prices, 5));
    return 0;
}
