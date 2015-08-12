/*
 * remote_duplicates_2.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        int pre = -1, next = 0;
        while(next < n){
            int current = A[next++];
            A[++pre] = current;
            if(next < n && A[next] == current){
                A[++pre] = current;
                next++;
            }
            while(next < n && A[next] == current) next++;
        }
        return pre + 1;
    }
};
int main(int argc, char *argv[])
{
    Solution *t = new Solution();
    int data[] = {1,1,1,2,2,3,3,3,4};
    printf("%d\n", t->removeDuplicates(data, 9));
    for (int i = 0; i < 7; ++i)
    {
        printf("%d ", data[i]);
    }
    return 0;
}


