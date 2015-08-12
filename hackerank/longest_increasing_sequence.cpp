#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
vector<int> dp;

int main() {
    cin>>n;
    for(int i = 0; i < n; ++i){
        int tmp;
        cin>>tmp;
        vector<int>::iterator low;
        low = lower_bound(dp.begin(), dp.end(), tmp);
        if(low == dp.end()){
            dp.push_back(tmp);
        }
        else{
            dp[low - dp.begin()] = tmp;
        }
    }
    cout<<dp.size()<<endl;
    return 0;
}
