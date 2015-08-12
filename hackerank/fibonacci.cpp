#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

LL N;
LL data[30];


int main() {
    cin>>data[0]>>data[1]>>N;
    for(int i = 2; i < N; ++i){
        data[i] = data[i - 1] * data[i - 1] + data[i - 2];
    }
    cout<<data[N - 1]<<endl;
    return 0;
}
