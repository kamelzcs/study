#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

#define SIZE 105
#define INF 1010

int N,K;

int dis[SIZE][SIZE];
bool used[SIZE];
int cnt[SIZE];

int main() {
    cin>>N>>K;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            dis[i][j] = INF;
        }
        dis[i][i] = 0;
    }
    for(int i = 0; i < N - 1; ++i){
        int start, end;
        cin>>start>>end;
        dis[start - 1][end - 1] = dis[end - 1][start - 1] = 1;
    }
    for(int k = 0; k < N; ++k){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            if(dis[i][j] > K){
                cnt[i]++;
            }
        }
    }
    int ans = 0;
    while(1){
        int max_cnt = 0, max_index = -1;
        for(int i = 0; i < N; ++i){
            if(used[i]){
                continue;
            }
            if(cnt[i] > max_cnt){
                max_cnt = i;
                max_index = i;
            }
        }
        if(max_index == -1){
            break;
        }
        used[max_index] = 1;
        ans++;
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < N; ++i){
            if(used[i]){
                continue;
            }
            for(int j = 0; j < N; ++j){
                if(used[j]){
                    continue;
                }
                if(dis[i][j] > K){
                    cnt[i]++;
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
