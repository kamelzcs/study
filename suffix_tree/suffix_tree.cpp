/*
 * suffix_tree.cpp
 * Copyright (C) 2014-11-06 zhao
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

#define ALPHA 27
#define LEN 100010
typedef struct node node;
struct node{
    int start, end;
    std::map<int, node*> child;
    node(){start = -1, end = -1;}
};
int main(){
    scanf("%s",str);
    len = strlen(str);
    build_suffix_tree(len);
    return 0;
}
