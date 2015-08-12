#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string data;

int func(int start, int end){
    if(start > end){
        return -1;
    }
    if(data[start] == data[end]){
        return func(start + 1, end - 1);
    }
    if(func(start + 1, end) < 0){
        return start;
    }
    return end;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin>>T;
    while(T--){
        cin>>data;
        cout<<func(0, data.size() - 1)<<endl;
    }
    return 0;
}
