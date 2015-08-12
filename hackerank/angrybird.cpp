#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

LL arr[100010];

void solve(LL arr[], LL N, LL K) {
    sort(arr, arr + N);
    LL ans;
    LL cur_sum = 0, cur_ans = 0;
    for(LL i = 0; i < K; ++i){
        cur_sum += arr[i];
        cur_ans += arr[i] * (1LL - K + 2LL * i);
    }
    ans = cur_ans;
    for(LL i = K; i < N; ++i){
        cur_sum -= arr[i - K];
        cur_ans -= arr[i - K] * (1LL - K);
        cur_ans -= 2LL * cur_sum;
        cur_ans += (K - 1LL) * arr[i];
        ans = min(ans, cur_ans);
        cur_sum += arr[i];
    }
    cout<<ans<<endl;
}
int main() {
    LL N, K;
     cin >> N >> K;
    for(LL i = 0; i < N; i++) {
        cin >> arr[i];
    }
     solve(arr, N, K);
    return 0;
}
