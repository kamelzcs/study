#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

#define SIZE 100010

typedef long long LL;

int T, n;

LL data[SIZE];
LL dp[SIZE];
LL sum[SIZE];


int main() {
    cin>>T;
    while(T--){
        cin>>n;
        memset(dp, 0, sizeof(dp));
        sum[0] = 0;
        for(int i = 1; i <= n; ++i){
            cin>>data[n + 1 - i];
        }
        for(int i = 1; i <= n; ++i){
            sum[i] = sum[i - 1] + data[i];
        }
        for(int i = 1; i <= n; ++i){
            for(int delta = 1; delta <= min(3, i); ++delta){
                LL opponent = dp[i - delta];
                dp[i] = max(dp[i], sum[i] - opponent);
            }
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
