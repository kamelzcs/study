#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define SIZE 3010

string str;
int len;
int largest[SIZE];
int paliLen[SIZE][SIZE];

void update(int pos, int delta){
    while(pos < SIZE){
        largest[pos] = max(largest[pos], delta);
        pos += (pos & -pos);
    }
}

int get(int pos){
    int ans = 1;
    while(pos){
        ans = max(ans, largest[pos]);
        pos -= (pos & -pos);
    }
    return ans;
}


int main() {
    cin>>str;
    len = str.size();
    for(int i = 0; i < len; ++i){
        paliLen[i][i] = 1;
    }
    for(int l = 2; l <= len; ++l){
        for(int start = 0; start + l <= len; ++start){
            int end = start + l - 1;
            paliLen[start][end] = max(paliLen[start][end - 1], paliLen[start + 1][end]);
            if(str[start] == str[end]){
                if(l > 2){
                    paliLen[start][end] = max(paliLen[start][end], paliLen[start + 1][end - 1] + 2);
                }
                else{
                    paliLen[start][end] = 2;
                }
            }
            update(end, paliLen[start][end]);
        }
    }
    int ans = 0;
    for(int second = 1; second < len; ++second){
        ans = max(paliLen[second][len - 1] * get(second - 1), ans);
    }
    cout<<ans<<endl;
    return 0;
}
