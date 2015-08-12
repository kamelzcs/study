/*
 * c.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-ThinkPad-X201>
 *
 * Distributed under terms of the MIT license.
 */

#include<memory.h>
#include<iostream>
#include<stdio.h>
using namespace std;
typedef long long LL;
#define REP(i, N) for (LL i = 0; i < (LL)N; i++)

char s[110];
int remain[110];
int trans[110];
int len;
string dp[110][110][8];

string self_max(string a, string b){
    if(a.empty()){
        return b;
    }
    return a;
}

int main(){
  cin>>s;
  len = strlen(s);
  REP(i, len){
    trans[len - 1 - i] = s[i] - '0';
  }
  remain[0] = 1;
  for(int i = 1; i <= 100; ++i){
    remain[i] = (remain[i - 1] * 10) % 8;
  }
  for(int i = 0; i <= len; ++i){
      for(int j = 0; j <= i; ++j){
          for(int k = 0; k < 8; ++k){
              dp[i][j][k] = "";
          }
      }
  }
  for(int i = 0; i <= len; ++i){
      for(int j = 0; j < i; ++j){
          dp[i][1][trans[j] % 8] = (char)('0' + trans[j]);
          if((trans[j] % 8) == 0){
              cout<<"YES"<<endl;
              cout<<dp[i][1][trans[j] % 8];
              return 0;
          }
      }
  }
  for(int m = 0; m < len; ++m){
      for(int n = 0; n <= m; ++n){
          for(int s = 0; s < 8; ++s){
              if(dp[m][n][s].empty()){
                  continue;
              }
              dp[m + 1][n][s] = self_max(dp[m + 1][n][s], dp[m][n][s]);
              int nxt_remain = (s + trans[m] * remain[n]) % 8;
              dp[m + 1][n + 1][nxt_remain] = self_max(dp[m + 1][n + 1][nxt_remain], (char)('0' + trans[m]) + dp[m][n][s]);
              if(nxt_remain == 0){
                  cout<<"YES"<<endl;
                  cout<<dp[m + 1][n + 1][nxt_remain]<<endl;
                  return 0;
              }
          }
      }
  }
  cout<<"NO"<<endl;
  return 0;
}
