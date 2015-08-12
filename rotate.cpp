#include<vector>
using namespace std;

class Solution {
public:
    int n;
    void dfs(int x, int y, int len, vector<vector<int> >& matrix){
        if(len <= 1){
            return;
        }
        int top = x, right = y + len - 1, bottom = x + len - 1, left = y;
        for(int j = 0; j < len - 1; ++j){
            int temp = matrix[top][left + j];
            swap(matrix[top + j][right], temp);
            swap(matrix[bottom][right - j], temp);
            swap(matrix[bottom - j][left], temp);
            swap(matrix[top][left + j], temp);
        }
        dfs(x + 1, y + 1, len - 2, matrix);
    }
    void rotate(vector<vector<int> >& matrix) {
        if(matrix.empty()){
            return;
        }
        n = matrix.size();
        dfs(0, 0, n, matrix);
    }
};
