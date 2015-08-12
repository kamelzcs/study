/*
 * contains_dupli.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> container;
        for(int data : nums){
            if(container.count(data)){
                return true;
            }
            container.insert(data);
        }
        return false;
    }
};
