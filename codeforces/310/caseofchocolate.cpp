/*
 * caseofchocolate.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdlib.h>
#include<stdio.h>
#include<memory.h>
#include<iostream>
#include<algorithm>
using namespace std;

#define size 200010

class Tree{
    public:
        int n;
        int *val;
        Tree(int n){
            this->n = n;
            val = new int[4 * n + 5];
            fill(val, val + 4 * n + 5, -1);
        }
        void update(int l, int r, int v){
            internalUpdate(0, 0, n - 1, l, r, v);
        }
        int get(int x){
            return internalGet(0, 0, n - 1, x);
        }
        void internalUpdate(int root, int rl, int rr, int l, int r, int v){
            if(l > r){
                return;
            }
            if(rl == l && rr == r){
                val[root] = max(val[root], v);
            }
            else{
                int mid = rl + (rr - rl) / 2;
                internalUpdate(2 * root + 1, rl, mid, l, min(r, mid), v);
                internalUpdate(2 * root + 2, mid + 1, rr, max(l, mid + 1), r, v);
            }
        }
        int internalGet(int root, int rl, int rr, int p){
            if(rl == rr){
                return val[root];
            }
            int res = val[root];
            int mid = rl + (rr - rl) / 2;
            if(p <= mid){
                return max(res, internalGet(2 * root + 1, rl, mid, p));
            }
            else{
                return max(res, internalGet(2 * root + 2, mid + 1, rr, p));
            }
        }
        ~Tree(){
            delete []val;
        }
};

int qx[size], qy[size];
int normalX[size], normalY[size];
int lenX, lenY;
char qup[size];

int N, Q;

int normalize(int *data, int n, int *out){
    int temp[n];
    memcpy(temp, data, sizeof(int) * n);
    sort(temp, temp + n);
    out[0] = temp[0];
    int ans = 0;
    for(int i = 1; i < n; ++i){
        if(temp[i] == out[ans]){
            continue;
        }
        out[++ans] = temp[i];
    }
    return ans + 1;
}


int main(){
    cin>>N>>Q;
    for(int i = 0; i < Q; ++i){
        scanf("%d %d %c", qx+i, qy+i, qup + i);
    }
    lenX = normalize(qx, Q, normalX);
    lenY = normalize(qy, Q, normalY);
    Tree *left = new Tree(lenX), *up = new Tree(lenY);
    for(int i = 0; i < Q; ++i){
        int x = lower_bound(normalX, normalX + lenX, qx[i]) - normalX;
        int y = lower_bound(normalY, normalY + lenY, qy[i]) - normalY;
        if(qup[i] == 'U'){
            int stopAt = up->get(x);
            if(stopAt == -1){
                printf("%d\n", normalY[y]);
            }
            else{
                printf("%d\n", normalY[y] - normalY[stopAt]);
            }
            up->update(x, x, y);
            left->update(stopAt + 1, y, x);
        }
        else{
            int stopAt = left->get(y);
            if(stopAt == -1){
                printf("%d\n", normalX[x]);
            }
            else{
                printf("%d\n", normalX[x] - normalX[stopAt]);
            }
            left->update(y, y, x);
            up->update(stopAt + 1, x, y);
        }
    }
    delete left;
    delete up;
    return 0;
}


