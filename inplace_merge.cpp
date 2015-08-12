/*
 * inplace_merge.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
void inplace_merge(int *data, int left, int right){
    int len = right - left, middle = (left + right)>>1;
    if (len<=1) return;
    int origin_right = right;
    working_sort(data, left, middle, middle);
    right = middle;
    while(right - left > 2){
        middle = (left + right) >> 1;
        working_sort(data, middle, right, left);
        working_merge(data, left, middle, right, origin_right, middle);
        right = middle;
    }
    for(int i = right, i >= l; i--){
        for(int j = i; j< origin_right-1 && data[j] >= data[j+1]; ++j){
            swap(data, j, j+1);
        }
    }
}
int main(){
    int data[] = {1,3,5,2};
    inplace_merge(data, 0, 4);
    for(int i=0; i<4; ++i){
        printf("%d ", data[i]);
    }
    return 0;
}



