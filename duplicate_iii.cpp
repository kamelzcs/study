/*
 * duplicate_iii.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


typedef long long LL;

class Solution {
public:
    map<LL, pair<LL, LL> > occupied;
    bool containsNearbyAlmostDuplicate(vector<int>& _nums, int k, int t) {
        if(_nums.empty()){
            return false;
        }
        if(_nums.size() < 2){
            return false;
        }
        if(k == 0){
            return false;
        }
        if(t < 0){
            return false;
        }
        LL min_value = *min_element(_nums.begin(), _nums.end());
        int n = _nums.size();
        vector<LL> nums;
        for(int i = 0; i < n; ++i){
            nums.push_back((LL)_nums[i] - min_value);
        }
        t++;
        occupied.clear();
        int left = 0, right = 0;
        for(; right < min(n, k + 1); ++right){
            LL bucket_pos = nums[right] / t;
            if(occupied.find(bucket_pos) != occupied.end()){
                return true;
            }
            occupied[bucket_pos] = make_pair(right, nums[right]);
        }
        for(; right < n; ++right){
            LL bucket_pos = nums[left++] / t;
            occupied.erase(bucket_pos);
            bucket_pos = nums[right] / t;
            if(occupied.find(bucket_pos) != occupied.end()){
                return true;
            }
            occupied[bucket_pos] = make_pair(right, nums[right]);
        }
        LL pre_pos = -1, pre_value = -1;
        for (auto& kv : occupied) {
            if(pre_pos < 0){
                pre_pos = kv.second.first;
                pre_value = kv.second.second;
            }
            else{
                int pos = kv.second.first, value = kv.second.second;
                if(pos - pre_pos > k){
                    continue;
                }
                if(value - pre_value < t){
                    return true;
                }
                pre_pos = pos;
                pre_value = value;
            }
        }
        return false;
    }
};
