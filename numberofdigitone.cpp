/*
 * numberofdigitone.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<iostream>
using namespace std;

class Solution {
public:
    int power10(int d){
        int ans = 1;
        while(d){
            ans *= 10;
            d--;
        }
        return ans;
    }
    int countDigitOne(int n) {
        if(n <= 0){
            return 0;
        }
        int len = 0;
        int digit[100];
        int temp = n;
        while(temp){
            digit[len++] = temp % 10;
            temp /= 10;
        }
        if(len == 1){
            return 1;
        }
        int base = power10(len - 1);
        if(digit[len - 1] == 1){
            return countDigitOne(base - 1) + countDigitOne(n % base) + (n % base) + 1;
        }
        else{
            return digit[len - 1] * countDigitOne(base - 1) + base + countDigitOne(n % base);
        }
    }
};

int main(){
    Solution *t = new Solution();
    cout<<t->countDigitOne(13)<<endl;
    cout<<t->countDigitOne(0)<<endl;
    return 0;
}

