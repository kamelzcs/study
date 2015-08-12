/*
 * denklek_paint_squares.cpp
 * Copyright (C) 2014 luxeys <info@luxeys.com>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<memory.h>
#include<string.h>
#define MOD 1000000007
long long cached[102][10][6562];
int valid[6562];
int width, height;
int get_ith_bit(int number, int ith){
    while(ith-- > 0){
        number/=3;
    }
    return number%3;
}
int power3(int ith){
    int ans = 1;
    while(ith-- > 0){
        ans*=3;
    }
    return ans;
}
void set_ith_bit(int& number, int ith, int bit){
    int current_bit = get_ith_bit(number, ith);
    number +=(bit - current_bit) * power3(ith);
}
int is_valid(int mask){
    int& res=valid[mask];
    if(res!=-1){
        return res;
    }
    for(int i=0; i<width; ++i){
        if(get_ith_bit(mask, i)==1){
            return res=0;
        }
    }
    return res=1;
}

long long ways(int x, int y, int mask){
    long long& res = cached[x][y][mask];
    if(res != -1){
        return res;
    }
    res = 0;
    if(x == height){
        if(is_valid(mask)){
            res = 1;
        }
        return res;
    }
    if( y == width){
        return res = ways(x + 1, 0, mask);
    }
    int ith_bit = get_ith_bit(mask, y);
    // do not color
    if(ith_bit != 1){
        int new_mask = mask;
        set_ith_bit(new_mask, y, 2);
        res += ways(x, y + 1, new_mask);
        res%=MOD;
    }
    // color it
    if(ith_bit != 0){
        int new_mask = mask;
        set_ith_bit(new_mask, y, 0);
        if(ith_bit == 1){
            set_ith_bit(new_mask, y, 1-get_ith_bit(new_mask, y));
        }
        if(y>0 && get_ith_bit(new_mask, y-1) != 2){
            set_ith_bit(new_mask, y-1, 1-get_ith_bit(new_mask, y-1));
            set_ith_bit(new_mask, y, 1-get_ith_bit(new_mask, y));
        }
        res += ways(x, y+1, new_mask);
        res%=MOD;
    }
    return res;
}

class DengklekPaintingSquares{
    public:
    int numSolutions(int N, int M){
        height = N;
        width = M;
        memset(cached, 0xff, sizeof(cached));
        memset(valid, 0xff, sizeof(valid));
        return ways(0, 0, power3(width)-1);
    }
};

int main(int argc, char *argv[])
{
    DengklekPaintingSquares *t = new DengklekPaintingSquares();
    printf("%d\n", t->numSolutions(1, 8));
    return 0;
}


