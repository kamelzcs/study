/*
 * unique_binary_search_tree.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>
#include<iostream>
using namespace std;

class Solution {
public:
    unsigned long long combination(unsigned long long n, unsigned long long k){
        if(k > n) return 0;
        unsigned long long ans = 1;
        for(unsigned long long d = 1; d <= k; ++d){
            ans *=(n--);
            ans/=d;
        }
        return ans;
    }
    unsigned long long cal_catalen(unsigned long long n){
        return combination(2*n, n);
    }
    int numTrees(int n) {
        unsigned long long k = n;
        return cal_catalen(k)/(k+1);
    }
};
int main(int argc, char *argv[])
{
    Solution *t = new Solution();
    cout << t->numTrees(3);
    return 0;
}


