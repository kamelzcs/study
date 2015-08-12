/*
 * rotate_array.c
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>


int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void rotate(int nums[], int n, int k) {
    k %= n;
    int common = gcd(n, k);
    int i = 0;
    for(; i < common; ++i){
        int current_index = i, current_value = nums[i], done = 0;
        while(done < n / common){
            int next_index = (current_index + k) % n;
            int temp = current_value;
            current_value = nums[next_index];
            nums[next_index] = temp;
            done++;
            current_index = next_index;
        }
    }
}

int main(int argc, char *argv[])
{
    int nums[] = {1, 2, 3, 4, 5, 6}, n = 6, k = 4;
    rotate(nums, n, k);
    int i;
    for(i = 0; i < n; ++i){
        printf("%d ", nums[i]);
    }
    return 0;
}
