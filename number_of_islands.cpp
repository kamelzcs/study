/*
 * number_of_islands.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */


bool visited[1000][1000];
class Solution {
public:
    int ans;
    int n, m;
    vector<vector<char>> grid;
    bool valid(int x,int y){
        if(x < 0 || x >= n){
            return false;
        }
        if(y < 0 || y >= m){
            return false;
        }
        return true;
    }
    void dfs(int x, int y){
        int dx[] = {0, -1, 0, 1};
        int dy[] = {-1, 0, 1, 0};
        visited[x][y] = true;
        for(int d = 0; d < 4; ++d){
            int nxt_x = x + dx[d], nxt_y = y + dy[d];
            if(valid(nxt_x, nxt_y)){
                if(grid[nxt_x][nxt_y] == '0'){
                    continue;
                }
                if(!visited[nxt_x][nxt_y]){
                    dfs(nxt_x, nxt_y);
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& _grid) {
        grid = _grid;
        if(grid.empty()){
            return 0;
        }
        memset(visited, 0, sizeof(visited));
        ans = 0;
        n = grid.size();
        m = grid[0].size();
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(visited[i][j]){
                    continue;
                }
                if(grid[i][j] == '0'){
                    continue;
                }
                ans++;
                dfs(i, j);
            }
        }
        return ans;
    }
};
