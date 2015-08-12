#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

#define MOD 1000000007
#define SIZE 410

typedef long long LL;

int T, N, M, S;
string data[2010];

int valid[SIZE][SIZE];
LL dp[2][SIZE][SIZE];
LL sums[SIZE][SIZE];

LL CHK(LL x){
    return (x + MOD) % MOD;
}

void ADD(LL &x, LL y){
    x = (x + y + MOD) % MOD;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin>>T;
    while(T--){
        memset(valid, 0, sizeof(valid));
        memset(dp, 0, sizeof(dp));
        cin>>N>>M>>S;
        S++;
        for(int i = 0; i < N; ++i){
            cin>>data[i];
        }
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                if(data[i][j] == 'P'){
                    continue;
                }
                valid[i - j + N - 1][i + j] = 1;
                if(data[i][j] == 'L'){
                    dp[1][i - j + N - 1][i + j] = 1;
                }
            }
        }
        for(int r = 0; r < M; ++r){
            int cur = r % 2, pre = (r + 1) % 2;
            for(int i = 0; i < 2 * N - 1; ++i){
                for(int j = 0; j < 2 * N - 1; ++j){
                    sums[i][j] = dp[pre][i][j];
                    if(i){
                        ADD(sums[i][j], sums[i - 1][j]);
                    }
                    if(j){
                        ADD(sums[i][j], sums[i][j - 1]);
                    }
                    if(i && j){
                        ADD(sums[i][j], -sums[i - 1][j - 1]);
                    }
                    //cout<<sums[i][j]<<" ";
                }
                //cout<<endl;
            }
            for(int mid_x = 0; mid_x < 2 * N - 1; ++mid_x){
                for(int mid_y = 0; mid_y < 2 * N - 1; ++mid_y){
                    dp[cur][mid_x][mid_y] = 0;
                    if(valid[mid_x][mid_y] == false){
                        continue;
                    }
                    int left_x = mid_x - S, right_x = min(mid_x + S - 1, 2 * N - 2);
                    int left_y = mid_y - S, right_y = min(mid_y + S - 1, 2 * N - 2);
                    dp[cur][mid_x][mid_y] = sums[right_x][right_y];
                    if(left_y >= 0){
                        ADD(dp[cur][mid_x][mid_y], -sums[right_x][left_y]);
                    }
                    if(left_x >= 0){
                        ADD(dp[cur][mid_x][mid_y], -sums[left_x][right_y]);
                    }
                    if(left_x >= 0 && left_y >= 0){
                        ADD(dp[cur][mid_x][mid_y], sums[left_x][left_y]);
                    }
                }
            }
        }
        LL ans = 0;
        for(int i = 0; i < 2 * N - 1; ++i){
            for(int j = 0; j < 2 * N - 1; ++j){
                ADD(ans, dp[(M + 1) % 2][i][j]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
