#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
    bool next_per(vector<int>& nums){
        int len = nums.size();
        int cur = len - 2;
        while(cur >= 0){
            if(nums[cur] < nums[cur + 1]){
                break;
            }
            cur--;
        }
        if(cur < 0){
            return false;
        }
        int swap_index = len - 1;
        while(nums[swap_index] <= nums[cur]){
            swap_index--;
        }
        swap(nums[cur], nums[swap_index]);
        reverse(nums.begin() + cur + 1, nums.end());
        return true;
    }
    vector<vector<int> > permute(vector<int>& nums) {
        vector<vector<int> > ans;
        if(nums.empty()){
            return ans;
        }
        sort(nums.begin(), nums.end());
        ans.push_back(nums);
        while(next_per(nums)){
            for(int item : nums){
                cout<<item<<" ";
            }
            cout<<endl;
            ans.push_back(nums);
        }
        return ans;
    }
};

int main(){
    Solution *t = new Solution();
    vector<int> temp{1, 1};
    t->permute(temp);
}
