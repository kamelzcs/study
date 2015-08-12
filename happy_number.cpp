/*
 * happy_number.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

class Solution {
public:
    int visit[1010];
    int trans(int n){
        int sum = 0;
        while(n){
            int remain = n % 10;
            sum += remain * remain;
            n /= 10;
        }
        return sum;
    }
    bool dfs(int x){
        if(x == 1){
            return true;
        }
        if(visit[x]){
            return false;
        }
        visit[x] = 1;
        return dfs(trans(x));
    }
    bool isHappy(int n) {
        memset(visit, 0, sizeof(visit));
        if(n == 1){
            return true;
        }
        return dfs(trans(n));
    }
};


