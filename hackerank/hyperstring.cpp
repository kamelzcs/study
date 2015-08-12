#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007

typedef long long LL;

int n, m;
vector<string> str, data;
LL dp[110];

LL CHK(LL x){
    return x % MOD;
}

bool cmp(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

bool valid(string s){
    if(s.empty()){
        return false;
    }
    for(int i = 0; i < data.size(); ++i){
        string cur = data[i];
        if(s.size() < cur.size()){
            break;
        }
        if(s.substr(0, cur.size()) == cur){
            if(!valid(s.substr(cur.size(), s.size() - cur.size()))){
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin>>n>>m;
    for(int i = 0; i < n; ++i){
        string tmp;
        cin>>tmp;
        str.push_back(tmp);
    }
    sort(str.begin(), str.end(), cmp);
    data.push_back(str[0]);
    for(int i = 1; i < str.size(); ++i){
        if(valid(str[i])){
            data.push_back(str[i]);
        }
    }
    dp[0] = 1;
    LL ans = 1;
    for(int i = 1; i <= m; ++i){
        for(int j = 0; j < data.size(); ++j){
            string cur = data[j];
            if(cur.size() > i){
                break;
            }
            dp[i] = CHK(dp[i] + dp[i - cur.size()]);
        }
        ans = CHK(ans + dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}
