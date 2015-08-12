/*
 * poj1509.cpp
 * Copyright (C) 2014-10-29 zhao
 *
 * Distributed under terms of the MIT license.
 */
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>

#define size 20010
#define bucket_size 123

#define PB push_back
#define MP make_pair

#define REP(i,n) for(i=0;i<(n);++i)
#define FOR(i,l,h) for(i=(l);i<=(h);++i)
#define FORD(i,h,l) for(i=(h);i>=(l);--i)

typedef std::vector<int> VI;
typedef std::vector<std::string> VS;
typedef std::vector<double> VD;
typedef long long LL;
typedef std::pair<int,int> PII;

char str[size];
int sa[size];
int wa[size], wb[size];
int *x, *y;
int ws[size];
int height[size];
int cmp(int *data, int x, int y, int l){
    return data[x] == data[y] && data[x + l] == data[y + l];
}
void build_sa(int len){
    memset(ws, 0, sizeof(ws));
    x = wa;
    y = wb;
    for(int i = 0; i < len; ++i){
        ws[x[i] = str[i]]++;
    }
    for(int i = 1; i < bucket_size; ++i){
        ws[i] += ws[i - 1];
    }
    for(int i = len - 1; i >= 0; --i){
        sa[--ws[x[i]]] = i;
    }
    int p = 0, m = bucket_size;
    for(int j = 1;; j *= 2){
        p = 0;
        for(int i = len - j; i < len; ++i){
            y[p++] = i;
        }
        for(int i = 0; i < len; ++i){
            if(sa[i] >= j){
                y[p++] = sa[i] - j;
            }
        }
        memset(ws, 0, sizeof(ws));
        for(int i = 0; i < len; ++i){
            ws[x[i]]++;
        }
        for(int i = 1; i < m; ++i){
            ws[i] += ws[i - 1];
        }
        for(int i = p - 1; i >= 0; --i){
            sa[--ws[x[y[i]]]] = y[i];
        }
        int *temp;
        temp = x;
        x = y;
        y = temp;
        x[sa[0]] = 0;
        p = 1;
        for(int i = 1; i < len; ++i){
            x[sa[i]] = (cmp(y, sa[i], sa[i - 1], j)) ? p - 1 : p++;
        }
        if(p == len) break;
        m = p;
    }
}

void build_height(int len){
    memset(height, 0, sizeof(height));
    int k = 0;
    for(int i = 0; i < len - 1; ++i){
        if(k > 0){
            k--;
        }
        int pre = sa[x[i] - 1];
        while(str[i + k] == str[pre + k]) k++;
        height[x[i]] = k;
    }
}

int find(int m){
    int i;
    for(i = 1; i < m; ++i){
        if(sa[i] < m / 2) break;
    }
    while(height[i + 1] >= m / 2) i++;
    return sa[i] + 1;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        char temp[size];
        scanf("%s", temp);
        strcpy(str,temp);
        strcat(str,temp);
        int len = strlen(str);
        build_sa(len + 1);
        build_height(len + 1);
        printf("%d\n", find(len + 1));
    }
    return 0;
}
