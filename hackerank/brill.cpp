#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define REP(i, N) for (int i = 0; i < (int)N; i++)

#define SIZE 8
#define MOD 1000000007

LL CHK(LL x){
  return x % MOD;
}

LL dp[21][9][(1<<8) + 2][(1<<8) + 2];
int data[21][10];
int N, M, T;

int clear_bit(int x, int bit){
  return x & (~(1<<bit));
}

int set_bit(int x, int bit){
  return x | (1<<bit);
}

LL func(int row, int col, int s1, int s2){
  if(row >= N){
    return 1;
  }
  if(col >= M){
    return func(row + 1, 0, s1, s2);
  }
  LL &res = dp[row][col][s1][s2];
  if(res != -1){
    return res;
  }
  //if(data[row][col] == 1){
    //res = func(row, col + 1, s1, s2);
    //return res;
  //}
  res = 0;
  // 1
  // ##
  //  #
  //  #
  if(row + 2 < N && col + 1 < M){
    if(data[row][col] == 0 && data[row][col + 1] == 0 && data[row + 1][col + 1] == 0 && data[row + 2][col + 1] == 0){
      if((s1 & (1<<col)) == 0 && (s1 & (1<<(col + 1))) == 0 && (s2 & (1<<(col + 1))) == 0){
        res = CHK(res + func(row, col + 2, (set_bit(clear_bit(s1, col), col + 1)), set_bit(clear_bit(s2, col), col + 1)));
      }
    }
  }

  // 2
  // ##
  // #
  // #
  if(row + 2 < N && col + 1 < M){
    if(data[row][col] == 0 && data[row][col + 1] == 0 && data[row + 1][col] == 0 && data[row + 2][col] == 0){
      if((s1 & (1<<col)) == 0 && (s1 & (1<<(col + 1))) == 0 && (s2 & (1<<(col))) == 0){
        res = CHK(res + func(row, col + 2, clear_bit(set_bit(s1, col), col + 1), clear_bit(set_bit(s2, col), col + 1)));
      }
    }
  }

  // 3
  // #
  // #
  // ##
  if(row + 2 < N && col + 1 < M){
    if(data[row][col] == 0 && data[row + 1][col] == 0 && data[row + 2][col] == 0 && data[row + 2][col + 1] == 0){
      if((s1 & (1<<col)) == 0 && (s2 & (1<<(col))) == 0){
        res = CHK(res + func(row, col + 1, set_bit(s1, col), (set_bit(set_bit(s2, col), col + 1))));
      }
    }
  }


  // 4
  //  #
  //  #
  // ##
  if(row + 2 < N && col + 1 < M){
    if(data[row][col + 1] == 0 && data[row + 1][col + 1] == 0 && data[row + 2][col] == 0 && data[row + 2][col + 1] == 0){
      if((s1 & (1<<(col + 1))) == 0 && (s2 & (1<<(col + 1))) == 0){
        if(data[row][col] == 1 || s1 & (1<<col)){
          res = CHK(res + func(row, col + 2, clear_bit(set_bit(s1, col + 1), col), (set_bit(set_bit(s2, col), col + 1))));
        }
      }
    }
  }

  // 5
  // #
  // ###
  if(row + 1 < N && col + 2 < M){
    if(data[row][col] == 0 && data[row + 1][col] == 0 && data[row + 1][col + 1] == 0 && data[row + 1][col + 2] == 0){
      if((s1 & (1<<(col))) == 0 && (s2 & (1<<(col))) == 0 && (s2 & (1<<(col + 1))) == 0 && (s2 & (1<<(col + 1))) == 0){
        res = CHK(res + func(row, col + 1, s1 | (1<<col) | (1<<(col + 1) | 1<<(col + 2)), s2));
      }
    }
  }

  // 6
  //   #
  // ###
  if(row + 1 < N && col + 2 < M){
    if(data[row][col + 2] == 0 && data[row + 1][col] == 0 && data[row + 1][col + 1] == 0 && data[row + 1][col + 2] == 0){
      if((s1 & (1<<(col + 2))) == 0 && (s2 & (1<<(col))) == 0 && (s2 & (1<<(col + 1))) == 0 && (s2 & (1<<(col + 1))) == 0){
        if((data[row][col] == 1 || s1 & (1<<col)) && (data[row][col + 1] && s1 & (1<<(col + 1)))){
          res = CHK(res + func(row, col + 1, s1 | (1<<col) | (1<<(col + 1) | 1<<(col + 2)), s2));
        }
      }
    }
  }

  // 7
  // ###
  // #
  if(row + 1 < N && col + 2 < M){
    if(data[row + 1][col] == 0 && data[row][col] == 0 && data[row][col + 1] == 0 && data[row][col + 2] == 0){
      if((s2 & (1<<(col))) == 0 && (s1 & (1<<(col))) == 0 && (s1 & (1<<(col + 1))) == 0 && (s1 & (1<<(col + 1))) == 0){
        res = CHK(res + func(row, col + 3, s1 | (1<<col), clear_bit(clear_bit(clear_bit(s2, col), col + 1), col + 2)));
      }
    }
  }

  // 8
  // ###
  //   #
  if(row + 1 < N && col + 2 < M){
    if(data[row + 1][col + 2] == 0 && data[row][col] == 0 && data[row][col + 1] == 0 && data[row][col + 2] == 0){
      if((s2 & (1<<(col + 2))) == 0 && (s1 & (1<<(col))) == 0 && (s1 & (1<<(col + 1))) == 0 && (s1 & (1<<(col + 2))) == 0){
        res = CHK(res + func(row, col + 3, set_bit(clear_bit(clear_bit(s1, col), col + 1), col + 2), clear_bit(clear_bit(clear_bit(s2, col), col + 1), col + 2)));
      }
    }
  }

  return res;
}

int main(){
  cin>>T;
  while(T--){
    cin>>N>>M;
    REP(i, N){
      string temp;
      cin>>temp;
      REP(j, M){
        data[i][j] = (temp[j] == '.' ? 0 : 1);
      }
    }
    memset(dp, 0xff, sizeof(dp));
    cout<<func(0, 0, 0, 0)<<endl;
  }
  return 0;
}
