/*
 * poj2774.cpp
 * Copyright (C) 2014-10-31 zhao
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
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

#define size 100010
#define bucket_size 124

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

int *x, *y;
int wa[2 * size], wb[2 * size];
int sa[2 * size], ws[2 * size], height[2 * size];
char str[2 * size];
int len_first, len_total;
bool cmp(int *data, int x, int y, int l){
    return data[x] == data[y] && data[x + l] == data[y + l];
}
#define get_index(index) (index < len_first ? 0 : 1)

void build_sa(int len){
    x = wa;
    y = wb;
    memset(ws, 0, sizeof(ws));
    for(int i = 0; i < len; ++i){
        ws[x[i] = str[i]]++;
    }
    for(int i = 1; i < bucket_size; ++i){
        ws[i] += ws[i - 1];
    }
    for(int i = 0; i < len; ++i){
        sa[--ws[x[i]]] = i;
    }

    int p = 0, m = bucket_size;
    for(int j = 1; ; j *= 2){
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
        for(int i = len - 1; i >= 0; --i){
            sa[--ws[x[y[i]]]] = y[i];
        }
        int *temp = x;
        x = y;
        y = temp;
        x[sa[0]] = 0;
        p = 1;
        for(int i = 1; i < len; ++i){
            x[sa[i]] = cmp(y, sa[i], sa[i - 1], j)? p - 1: p++;
        }
        if(p == len) break;
        m = p;
    }
}
void build_height(int len){
    memset(height, 0, sizeof(height));
    int h = 0;
    for(int i = 0; i < len - 1; ++i){
        if(h > 0) h--;
        int pre = sa[x[i] - 1];
        while(str[i + h] == str[pre + h]) h++;
        height[x[i]] = h;
    }
}
int find(int len){
    int ans = 0;
    for(int i = 1; i < len; ++i){
        int current = sa[i], pre = sa[i - 1];
        if(get_index(current) != get_index(pre)){
            if(height[i] > ans) ans = height[i];
        }
    }
    return ans;
}
int main(){
    scanf("%s", str);
    len_first = strlen(str);
    str[len_first] = 'A';
    scanf("%s", str + len_first + 1);
    len_total = strlen(str);
    build_sa(len_total + 1);
    build_height(len_total + 1);
    printf("%d\n", find(len_total + 1));
    return 0;
}

