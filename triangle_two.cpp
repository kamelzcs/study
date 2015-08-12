/*
 * triangle_two.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stab.h>
#include<vector>
#include<memory.h>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
       vector<int> pre,now;
       now.push_back(1);
       for(int i=1; i<=rowIndex; ++i){
           pre = move(now);
           for(int j=0; j<=i; ++j){
               int temp = 0;
               if(j - 1 >= 0){
                   temp += pre[j-1];
               }
               if(j < (int)pre.size()){
                   temp += pre[j];
               }
               now.push_back(temp);
               cout<< temp << " ";
           }
           cout<<endl;
       }
       return now;
    }
};

int main(int argc, char *argv[])
{
    Solution *t = new Solution();
    t->getRow(3);
    return 0;
}
