/*
 * count_sort.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>
void count_sort(int *data, int *output, int len, int K){
    int base[K+1];
    memset(base, 0, sizeof(base));
    for (int i = 0; i < len; ++i)
    {
        base[data[i]]++;
    }
    for(int i=1; i<K; ++i) base[i] += base[i-1];
    for(int i=0; i<len; ++i){
        output[--base[data[i]]] = data[i];
    }
}
int main(int argc, char *argv[])
{
    int data[] = {1,3,2,4};
    int output[5];
    count_sort(data, output, 4, 5);
    for (int i = 0; i < 4; ++i)
    {
        printf("%d ", output[i]);
    }
    return 0;
}


