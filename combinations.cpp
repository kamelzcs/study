class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > ans;
        int base = (1<<k) - 1;
        while(base < (1<<n)){
            vector<int> res;
            for(int j = 0; j < n; ++j){
                if((1<<j) & base){
                    res.push_back(j + 1);
                }
            }
            ans.push_back(res);
            int least = base & (-base);
            int bigger = base + least;
            int ones = base & (~bigger);
            base = bigger | (ones / least / 2);
        }
        return ans;
    }
};


