#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <set>
using namespace std;

int dp[2010][2010];
set<int> values;
vector<int> elements;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T, n, k;
    cin>>T;
    while(T--){
        values.clear();
        elements.clear();
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        cin>>n>>k;
        for(int i = 0; i < n; ++i){
            int temp;
            cin>>temp;
            values.insert(temp);
        }
        for(int v: values){
            elements.push_back(v);
        }
        int ans = 0;
        for(int i = 0; i <= elements.size(); ++i){
            for(int j = 0; j <= k; ++j){
                dp[i + 1][j] |= dp[i][j];
                if(i){
                    if(dp[i][j]){
                        if(j + elements[i - 1] <= k){
                            dp[i][j + elements[i - 1]] = 1;
                        }
                    }
                }
                if(dp[i][j]){
                    ans = max(ans, j);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
