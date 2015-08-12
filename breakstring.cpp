/*
 * breakstring.cpp
 * Copyright (C) 2014 zhao
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <utility>

#define H 1002

using namespace std;

long long min_value[H][H], min_pos[H][H];
int break_point[H];
void init(){
    memset(min_value, 0x1f, sizeof(min_value));
}

int main(int argc, char *argv[])
{
    int length, num_breaks;
    while(scanf("%d", &length)!=EOF){
        scanf("%d", &num_breaks);
        break_point[0] = 0;
        break_point[num_breaks+1] = length;
        for(int i=1; i<=num_breaks; ++i){
            scanf("%d", break_point + i);
        }
        init();
        num_breaks+=2;
        for(int len=1; len<=num_breaks; ++len){
            for(int start = 0; start + len <= num_breaks; ++start){
                int end = start + len - 1;
                if(len<=2){
                    min_value[start][end] = 0;
                    min_pos[start][end] = end;
                    continue;
                }
                for(int k=min_pos[start][end-1]; k<=min_pos[start+1][end]; ++k){
                    long long temp = min_value[start][k] + min_value[k][end];
                    if(temp < min_value[start][end]){
                        min_value[start][end] = temp;
                        min_pos[start][end] = k;
                    }
                }
                min_value[start][end] += break_point[end] - break_point[start];
            }
        }
        printf("%lld\n", min_value[0][num_breaks-1]);
    }
    return 0;
}


