#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string s, t;
int dp[2][5011];

int main() {
    cin>>s>>t;
    int len_s = s.size(), len_t = t.size();
    for(int i = 0; i <= len_s; ++i){
        for(int j = 0; j <= len_t; ++j){
            if(i){
                dp[i % 2][j] = dp[(i + 1) % 2][j];
            }
            if(j){
                dp[i % 2][j] = max(dp[i % 2][j], dp[i % 2][j - 1]);
            }
            if(i && j){
                dp[i % 2][j] = max(dp[i % 2][j], dp[(i + 1) % 2][j - 1] + (s[i - 1] == t[j - 1] ? 1 : 0));
            }
        }
    }
    cout<<dp[len_s % 2][len_t];
    return 0;
}
