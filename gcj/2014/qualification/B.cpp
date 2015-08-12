/*
 * B.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<algorithm>
#include<functional>
using namespace std;
int T;
double C, F, X, ans;
void dfs(double income, double now_time){
    if(now_time > ans){
        return;
    }
    ans = min(ans, X / income + now_time);
    double delta = C / income;
    dfs(income + F, now_time + delta);
}
int main(){
    scanf("%d", &T);
    for(int loop = 1; loop <= T; ++loop){
        scanf("%lf%lf%lf", &C, &F, &X);
        ans = X * X;
        double income = 2.0, now_time = 0.0;
        while(1){
            if(now_time > ans){
                break;
            }
            ans = min(ans, X / income + now_time);
            double delta = C / income;
            income += F;
            now_time +=  delta;
        }
        printf("Case #%d: %7lf\n", loop, ans);
    }
    return 0;
}

