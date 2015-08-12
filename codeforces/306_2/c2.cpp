/*
 * c2.cpp
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
int digit[110];
int len;
bool dp[110][8];
pair<int,int> pre[110][8];

int main(){
  cin>>s;
  len = strlen(s);
  REP(i, len){
    digit[i] = s[i] - '0';
  }
  for(int i = 0; i <= len; ++i){
    for(int j = 0; j < 8; ++j){
      dp[i][j] = false;
    }
  }
  memset(pre, 0xff, sizeof(pre));
  for(int i = 1; i <= len; ++i){
    if(dp[i][digit[i - 1] % 8] == false){
      dp[i][digit[i - 1] % 8] = true;
      pre[i][digit[i - 1] % 8] = make_pair(i - 1, 0);
    }
  }
  for(int i = 1; i < len; ++i){
    for(int j = 0; j < 8; ++j){
      if(dp[i][j] == false){
        continue;
      }
      if(dp[i + 1][j] == false){
        dp[i + 1][j] = true;
        pre[i + 1][j] = pre[i][j];
      }
      int nxt_state = (j * 10 + digit[i]) % 8;
      if(dp[i + 1][nxt_state] == false){
        dp[i + 1][nxt_state] = true;
        pre[i + 1][nxt_state] = make_pair(i, j);
      }
    }
  }
  if(dp[len][0] == false){
    puts("NO");
  }
  else{
    puts("YES");
    string ans = "";
    pair<int, int> tp = pre[len][0];
    while(true){
      int pos = tp.first, remain = tp.second;
      ans = s[pos] + ans;
      tp = pre[pos][remain];
      if(remain == 0){
        break;
      }
    }
    cout<<ans<<endl;
  }
  return 0;
}
