/*
 * contains_duplicate_ii.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        if(k <= 0){
            return false;
        }
        if(nums.empty()){
            return false;
        }
        int n = nums.size();
        unordered_set<int> container;
        int left = 0, right = 0;
        for(; right < min(k + 1, n); ++right){
            if(container.count(nums[right])){
                return true;
            }
            container.insert(nums[right]);
        }
        for( ;right < n; ++right){
            container.erase(nums[left]);
            left++;
            if(container.count(nums[right])){
                return true;
            }
            container.insert(nums[right]);
        }
        return false;
    }
};


