#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define SIZE 510

char map[SIZE][SIZE];

int col[SIZE][SIZE];

int m,n;

bool connect(int data[SIZE][SIZE], int x1, int y1, int x2, int y2){
    return data[x2][y2] - data[x1][y1] == (x2 - x1 + y2 - y1);
}

int main() {
    cin>>m>>n;
    for(int i = 0; i < m; ++i){
        cin>>map[i];
    }
    for(int j = 1; j <= n; ++j){
        for(int i = 1; i <= m; ++i){
            col[i][j] = col[i - 1][j] + (map[i - 1][j - 1] == '.' ? 1 : 0);
        }
    }
    int ans = 0;
    for(int up = 1; up <= m; ++up){
        for(int down = up + 1; down <= m; ++down){
            int l = -1;
            for(int r = 1; r <= n; ++r){
                if(map[up - 1][r - 1] != '.' || map[down - 1][r - 1] != '.'){
                    l = -1;
                    continue;
                }
                if(connect(col, up - 1, r, down, r)){
                    if(l == -1){
                        l = r;
                    }
                    else{
                        ans = max(ans, down - up + r - l);
                    }
                }
            }
        }
    }
    if(!ans){
        puts("impossible");
    }
    else{
        cout<<2 * ans<<endl;
    }
    return 0;
}
