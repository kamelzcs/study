/*
 * num_of_1.c
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


int hammingWeight(uint32_t n) {
    int ans = 0;
    while(n){
        ans++;
        n ^= (n & (n ^ (n - 1)));
    }
    return ans;
}
