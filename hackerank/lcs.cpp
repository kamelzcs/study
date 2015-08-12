#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> dp[110][110];
int s[110], t[110];
int m,n;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>m>>n;
    for(int i = 1; i <= m; ++i){
        cin>>s[i];
    }
    for(int i = 1; i <= n; ++i){
        cin>>t[i];
    }
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            if(dp[i - 1][j].size() > dp[i][j - 1].size()){
                dp[i][j] = dp[i - 1][j];
            }
            else{
                dp[i][j] = dp[i][j - 1];
            }
            if(s[i] == t[j]){
                if(dp[i - 1][j - 1].size() + 1 > dp[i][j].size()){
                    dp[i][j] = dp[i - 1][j - 1];
                    dp[i][j].push_back(s[i]);
                }
            }
        }
    }
    for(int i = 0; i < dp[m][n].size(); ++i){
        cout<<dp[m][n][i]<<" ";
    }
    cout<<endl;
    return 0;
}
