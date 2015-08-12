/*
 * summary_ranges.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<string>
#include<vector>
#include<iostream>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ans;
        if(nums.empty()){
            return ans;
        }
        int len = (int)nums.size();
        int current = 0;
        while(current < len){
            int next = current + 1;
            while(next < len && nums[next] - nums[current] == next - current){
                next++;
            }
            ostringstream ss;
            ss<<nums[current];
            if(next > current + 1){
                ss<<"->"<<nums[current] + next - current - 1;
            }
            ans.push_back(ss.str());
            current = next;
        }
        return ans;
    }
};

int main(){
    Solution *t = new Solution();
    vector<int> tt = {1, 2, 3};
    t->summaryRanges(tt);
}


