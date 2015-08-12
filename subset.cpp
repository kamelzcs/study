class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > ans;
        set<vector<int> > cached;
        int len = nums.size();
        int full_mask = (1<<len) - 1;
        sort(nums.begin(), nums.end());
        for(int mask = full_mask; ; mask = (mask - 1) & full_mask){
            vector<int> temp;
            for(int i = 0; i < len; ++i){
                if((1<<i) & mask){
                    temp.push_back(nums[i]);
                }
            }
            if(cached.find(temp) == cached.end()){
                ans.push_back(temp);
                cached.insert(temp);
            }
            if(!mask){
                break;
            }
        }
        return ans;
    }
};


