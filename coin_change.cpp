#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

long long dp[60][260];
int n, m;
int c[60];


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>n>>m;
    for(int i = 0; i < m; ++i){
        cin>>c[i];
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i = 1; i <= m; ++i){
        for(int j = 0; j < c[i - 1]; ++j){
            dp[i][j] = dp[i - 1][j];
        }
        for(int j = c[i - 1]; j <= n; ++j){
            dp[i][j] += dp[i][j - c[i - 1]] + dp[i - 1][j];
        }
    }
    cout<<dp[m][n];
    return 0;
}
