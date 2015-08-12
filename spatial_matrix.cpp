#include<vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > ans;
    int n;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    void dfs(int x, int y, int val, int dir, int left){
        ans[x][y] = val;
        if(left == 1){
            return;
        }
        int nxt_x, nxt_y, nxt_dir;
        for(int i = 0; i < 4; ++i){
            nxt_dir = (dir + i) % 4;
            nxt_x = x + dx[nxt_dir], nxt_y = y + dy[nxt_dir];
            if(nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= n){
                continue;
            }
            if(ans[nxt_x][nxt_y]){
                continue;
            }
            break;
        }
        dfs(nxt_x, nxt_y, val + 1, nxt_dir, left - 1);
    }
    vector<vector<int> > generateMatrix(int _n) {
        n = _n;
        ans = vector<vector<int> > (n, vector<int>(n, 0));
        if(!n){
            return ans;
        }
        dfs(0, 0, 1, 0, n * n);
        return ans;
    }
};
