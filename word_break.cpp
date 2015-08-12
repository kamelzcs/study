/*
 * word_break.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<iostream>
#include<algorithm>
#include<functional>
#include<unordered_set>
#include<vector>
using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        int n = s.size();
        for(int i = 0; i <= n; ++i){
            dp.push_back(vector<string>());
        }
        if(n == 0) return vector<string>();
        for(int i = 1; i <= n; ++i){
            for(int j = i - 1; j >= 1; --j){
                if(dp[j].size() == 0) continue;
                string key = s.substr(j, i - j);
                if(dict.find(key) != dict.end()){
                    for(vector<string>::iterator it = dp[j].begin(); it != dp[j].end(); ++it){
                        dp[i].push_back(*it + " " + key);
                    }
                }
            }
            string origin = s.substr(0, i);
            if(dict.find(origin) != dict.end()){
                dp[i].push_back(origin);
            }
        }
        return dp[n];
    }
private:
    vector<vector<string>> dp;
};
int main(){
    Solution *t = new Solution();
    unordered_set<string> first({"a", "b"});
    vector<string> ans = t->wordBreak("ab", first);
    for(vector<string>::iterator it = ans.begin(); it != ans.end(); ++it){
        cout << *it <<endl;
    }
    return 0;
}
