/*
 * dupliate_iii_2.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


typedef long long LL;

class Solution {
public:
    map<LL, int> occur;
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(nums.empty()){
            return false;
        }
        int l = 0, right;
        for(right = 0; right < nums.size(); ++right){
            if(right - l > k){
                occur.erase(nums[l++]);
            }
            auto it = occur.lower_bound((LL)nums[right] - t);
            if(it != occur.end() && abs(it->first - nums[right]) <= t){
                return true;
            }
            occur[nums[right]] = right;
        }
        return false;
    }
};
