#include<string>
#include<iostream>
#include<memory.h>
using namespace std;

#define INF 0x1f1f1f1f

int dp[2][10010];
class Solution {
public:
    int minDistance(string word1, string word2) {
        memset(dp, 0x1f, sizeof(dp));
        int len_a = word1.size(), len_b = word2.size();
        dp[0][0] = 0;
        for(int i = 0; i <= len_a; ++i){
            for(int j = 0; j <= len_b; ++j){
                // delete
                if(i){
                    dp[i % 2][j] = dp[(i + 1) % 2][j] + 1;
                }
                //insert
                if(j){
                    dp[i % 2][j] = min(dp[i % 2][j], dp[i % 2][j - 1] + 1);
                }
                //update
                if(i && j){
                    dp[i % 2][j] = min(dp[i % 2][j], dp[(i + 1) % 2][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1));
                }
            }
        }
        return dp[len_a % 2][len_b];
    }
};

int main(){
    Solution *t = new Solution();
    cout<<t->minDistance("aab", "ab");
    cout<<t->minDistance("a", "b");
    cout<<t->minDistance("", "b");
    cout<<t->minDistance("a", "");
    return 0;
}
