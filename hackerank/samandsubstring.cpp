#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007

#define SIZE 200010

typedef long long LL;

LL single[SIZE], sums[SIZE];

string str;
LL len;

int main() {
    cin>>str;
    len = str.size();
    single[0] = sums[0] = 1;
    for(int i = 1; i <= len; ++i){
        single[i] = (single[i - 1] * 10) % MOD;
        sums[i] = (sums[i - 1] + single[i]) % MOD;
    }
    LL ans = 0;
    for(int i = 0; i < len; ++i){
        ans = (ans + (((LL)(str[i] - '0') * sums[len - 1 - i] * (LL)(i + 1)) % MOD)) % MOD;
    }
    cout<<ans<<endl;
    return 0;
}
