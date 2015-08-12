class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()){
            return false;
        }
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while(1){
            if(y < 0 || x >= m){
                break;
            }
            if(matrix[x][y] > target){
                y--;
            }
            else if(matrix[x][y] < target){
                x++;
            }
            else{
                return true;
            }
        }
        return false;
    }
};
