#include <bits/stdc++.h>
using namespace std;
#define REP(i, N) for (int i = 0; i < (int)N; i++)

#define SIZE 8
#define MOD 1000000007
#define MP make_pair

typedef long long LL;
typedef pair<LL, pair<LL, LL > > PL ;

map<PL, LL> cache;

LL CHK(LL x){
  return x % MOD;
}

int data[21][10];
int N, M, T;

int clear_bit(int x, int bit){
  return x & (~(1<<bit));
}

int set_bit(int x, int bit){
  return x | (1<<bit);
}

bool valid(int x, int bit){
  return (x & (1<<bit)) == 0;
}

LL func(int row, int col, int s1, int s2, int s3){
  if(row >= N){
    return 1;
  }
  if(col >= M){
    PL res = MP(row + 1, MP(s2, s3));
    if(cache.find(res) != cache.end()){
      return cache[res];
    }
    return cache[res] = func(row + 1, 0, s2, s3, 0);
  }
  if(data[row][col] == 1 || s1 & (1<<col)){
    return func(row, col + 1, s1, s2, s3);
  }
  LL ans = 0;
  // 1
  // ##
  //  #
  //  #
  if(row + 2 < N && col + 1 < M){
    if(data[row][col + 1] == 0 && data[row + 1][col + 1] == 0 && data[row + 2][col + 1] == 0){
      if((s1 & (1<<(col + 1))) == 0 && (s2 & (1<<(col + 1))) == 0 && valid(s3, col + 1)){
        ans = CHK(ans + func(row, col + 2, s1, set_bit(s2, col + 1), set_bit(s3, col + 1)));
      }
    }
  }

  // 2
  // ##
  // #
  // #
  if(row + 2 < N && col + 1 < M){
    if(data[row][col + 1] == 0 && data[row + 1][col] == 0 && data[row + 2][col] == 0){
      if((s1 & (1<<(col + 1))) == 0 && (s2 & (1<<(col))) == 0 && valid(s3, col)){
        ans = CHK(ans + func(row, col + 2, s1, set_bit(s2, col), set_bit(s3, col)));
      }
    }
  }

  // 3
  // #
  // #
  // ##
  if(row + 2 < N && col + 1 < M){
    if(data[row + 1][col] == 0 && data[row + 2][col] == 0 && data[row + 2][col + 1] == 0){
      if((s2 & (1<<(col))) == 0 && valid(s3, col) && valid(s3, col + 1)){
        ans = CHK(ans + func(row, col + 1, s1, set_bit(s2, col), set_bit(set_bit(s3, col), col + 1)));
      }
    }
  }

  // 4
  //  #
  //  #
  // ##
  if(row + 2 < N && col >= 1){
    if(data[row + 1][col] == 0 && data[row + 2][col] == 0 && data[row + 2][col - 1] == 0){
      if((s2 & (1<<(col))) == 0 && valid(s3, col) && valid(s3, col - 1)){
        ans = CHK(ans + func(row, col + 1, s1, set_bit(s2, col), (set_bit(set_bit(s3, col), col - 1))));
      }
    }
  }

  // 5
  // #
  // ###
  if(row + 1 < N && col + 2 < M){
    if(data[row + 1][col] == 0 && data[row + 1][col + 1] == 0 && data[row + 1][col + 2] == 0){
      if((s2 & (1<<(col))) == 0 && (s2 & (1<<(col + 1))) == 0 && (s2 & (1<<(col + 2))) == 0){
        ans = CHK(ans + func(row, col + 1, s1, s2 | (1<<col) | (1<<(col + 1) | 1<<(col + 2)), s3));
      }
    }
  }

  // 8
  // ###
  //   #
  if(row + 1 < N && col + 2 < M){
    if(data[row + 1][col + 2] == 0 && data[row][col + 1] == 0 && data[row][col + 2] == 0){
      if((s2 & (1<<(col + 2))) == 0 && (s1 & (1<<(col + 1))) == 0 && (s1 & (1<<(col + 2))) == 0){
        ans = CHK(ans + func(row, col + 3, s1, set_bit(s2, col + 2), s3));
      }
    }
  }

  // 6
  //   #
  // ###
  if(row + 1 < N && col >= 2){
    if(data[row + 1][col] == 0 && data[row + 1][col - 1] == 0 && data[row + 1][col - 2] == 0){
      if((s2 & (1<<(col))) == 0 && (s2 & (1<<(col - 1))) == 0 && (s2 & (1<<(col - 2))) == 0){
        ans = CHK(ans + func(row, col + 1, s1, s2 | (1<<col) | (1<<(col - 1) | 1<<(col - 2)), s3));
      }
    }
  }

  // 7
  // ###
  // #
  if(row + 1 < N && col + 2 < M){
    if(data[row + 1][col] == 0 && data[row][col + 1] == 0 && data[row][col + 2] == 0){
      if((s2 & (1<<(col))) == 0 && (s1 & (1<<(col + 1))) == 0 && (s1 & (1<<(col + 2))) == 0){
        ans = CHK(ans + func(row, col + 3, s1, set_bit(s2, col), s3));
      }
    }
  }

  return ans;
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
    cache.clear();
    cout<<func(0, 0, 0, 0, 0)<<endl;
  }
  return 0;
}
