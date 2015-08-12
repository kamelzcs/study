/*
 * single_number_2.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

class Solution {
public:
    int singleNumber(int A[], int n) {
        int bits[40];
        for(int i=0; i<40; ++i) bits[i] = 0;
        for(int i=0; i<n; ++i){
            for(int j=0; j<32; ++j){
                if(A[i]&(1<<j)) bits[j] = (bits[j]+1)%3;
            }
        }
        int ans=0;
        for(int i=0; i<32; ++i){
            if(bits[i]) ans|=(1<<i);
        }
        return ans;
    }
};


