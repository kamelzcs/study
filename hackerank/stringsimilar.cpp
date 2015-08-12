#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;
/* Head ends here */

int z[100010];

long long int stringSimilarity(char a[]) {
    memset(z, 0, sizeof(z));
    int l = 0, r = 0;
    int len = strlen(a);
    long long ans = len;
    for(int i = 1; i < len; ++i){
        if(i <= r){
            z[i] = min(z[i - l], r - i + 1);
        }
        while(i + z[i] < len && a[i + z[i]] == a[z[i]]){
            z[i]++;
        }
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
        ans += z[i];
    }
    return ans;
}
int main() {
    int t, i;
    scanf("%d",&t);
    char a[100001];
    for (i=0;i<t;i++) {
        scanf("%s",a);
        long long int res=stringSimilarity(a);
        printf("%lld\n",res);  
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
