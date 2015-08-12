/*
 * quicksort.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
void swap(int *data, int x, int y){
    int temp = data[x];
    data[x] = data[y];
    data[y] = temp;
}
int partition(int *data, int pivot, int left, int right){
    int pivot_index = left-1;
    for (int i = left; i < right; ++i)
    {
        if(data[i] < pivot){
            pivot_index++;
            swap(data, pivot_index, i);
        }
    }
    return pivot_index+1;
}
void quick_sort(int *data, int left, int right){
    int len = right - left;
    if(len<=1) return;
    int pivot = data[left];
    int pivot_index;
    pivot_index = partition(data, pivot, left, right);
    quick_sort(data, left, pivot_index);
    quick_sort(data, pivot_index+1, right);
}
int main(int argc, char *argv[])
{
    int data[] = {10,4,3,2};
    quick_sort(data, 0, 4);
    for(int i=0; i<4; ++i) printf("%d ", data[i]);
    return 0;
}


