#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

typedef long long LL;

#define SIZE 210

#define MOD 1000000007

LL dp[SIZE][SIZE];

int n;
int len;
string str;

LL CHK(LL x){
    return ((x % MOD) + MOD) % MOD;
}

LL func(string &source, string &dest){
    int l_source = source.size(), l_dest = dest.size();
    memset(dp, 0, sizeof(dp));
    if(dest[0] == source[0]){
        dp[0][0] = 1;
    }
    for(int i = 1; i < l_dest; ++i){
        dp[0][i] = (dp[0][i - 1] + ((dest[i] == source[0] ? 1 : 0)));
    }
    for(int i = 1; i < l_source; ++i){
        for(int j = 0; j < l_dest; ++j){
            dp[i][j] = dp[i - 1][j];
            if(j){
                dp[i][j] = CHK(dp[i][j] + dp[i][j - 1] - dp[i - 1][j - 1]);
                if(source[i] == dest[j]){
                    dp[i][j] = CHK(dp[i][j] + dp[i - 1][j - 1]);
                }
            }
        }
    }
    return dp[l_source - 1][l_dest - 1];
}

int main() {
    cin>>n;
    while(n--){
        cin>>str;
        len = str.size();
        LL ans = 0;
        for(int i = 1; i < len; ++i){
            string source, dest;
            source = str.substr(i, len - i);
            dest = str.substr(0, i);
            ans = (ans + func(source, dest)) % MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}
