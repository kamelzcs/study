#include<vector>
#include<iostream>
#include<string>
#include<set>
using namespace std;


class Solution {
public:
    int len;
    string str;
    vector<int> dp[110][110];
    bool operator_exist(int start, int end){
        for(int i = start; i<= end; ++i){
            if(str[i] > '9' || str[i] < '0'){
                return true;
            }
        }
        return false;
    }
    vector<int> func(int start, int end){
        vector<int> &ans = dp[start][end];
        if(!ans.empty()){
            return ans;
        }
        if(!operator_exist(start, end)){
            ans.push_back(stoi(str.substr(start, end - start + 1)));
        }
        else{
            for(int pos = start + 1; pos < end; ++pos){
                if(operator_exist(pos, pos)){
                    vector<int> first = func(start, pos - 1), second = func(pos + 1, end);
                    for(int n1: first){
                        for(int n2: second){
                            if(str[pos] == '-'){
                                ans.push_back(n1 - n2);
                            }
                            else if(str[pos] == '+'){
                                ans.push_back(n1 + n2);
                            }
                            else if(str[pos] == '*'){
                                ans.push_back(n1 * n2);
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
    vector<int> diffWaysToCompute(string input) {
        str = input;
        len = input.size();
        return func(0, len - 1);
    }
};

int main(){
    Solution *t = new Solution();
    vector<int> tmp = t->diffWaysToCompute("0");
    for(int v: tmp){
        cout<<v<<endl;
    }
}
