#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
using namespace std;

#define S 400010
#define INF 0x3f3f3f3f3f3f3f3f
long long road[S], flight[S], delta[S];
long long dp[2][42][2];

class RoadOrFlightHard {
    public:
    long long minTime(int N, int roadFirst, int roadProd, int roadAdd, int roadMod, int flightFirst, int flightProd, int flightAdd, int flightMod, int K) {
        road[0] = roadFirst % roadMod;
        flight[0] = flightFirst % flightMod;
        long long ans = 0;
        for(int i=1; i<N; ++i){
            road[i] = (road[i-1] * roadProd + roadAdd) % roadMod;
            flight[i] = (flight[i-1] * flightProd + flightAdd) % flightMod;
        }
        for(int i=0; i<N; ++i){
            delta[i] = road[i] - flight[i];
            ans += road[i];
        }
        for(int j=0; j<=K; ++j){
            for(int k=0; k<2; ++k){
                dp[0][j][k] = -INF;
            }
        }
        dp[0][0][0] = 0;
        for(int i=0; i<N; ++i){
            for(int j=0; j<=K; ++j){
                dp[(i+1)&1][j][0] = dp[(i+1)&1][j][1] = -INF;
            }
            for(int j=0; j<=K; ++j){
                dp[(i+1)&1][j][0] = max(dp[(i+1)&1][j][0], max(dp[i&1][j][0], dp[i&1][j][1]));
                dp[(i+1)&1][j][1] = max(dp[(i+1)&1][j][1], dp[i&1][j][1] + delta[i]);
                dp[(i+1)&1][j+1][1] = max(dp[(i+1)&1][j+1][1], dp[i&1][j][0] + delta[i]);
            }
        }
        long long temp = 0;
        for(int i=0; i<=K; ++i){
            temp = max(temp, dp[N&1][i][0]);
            temp = max(temp, dp[N&1][i][1]);
        }
        return ans - temp;
    }
};

// CUT begin
ifstream data("RoadOrFlightHard.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int N, int roadFirst, int roadProd, int roadAdd, int roadMod, int flightFirst, int flightProd, int flightAdd, int flightMod, int K, long long __expected) {
    time_t startClock = clock();
    RoadOrFlightHard *instance = new RoadOrFlightHard();
    long long __result = instance->minTime(N, roadFirst, roadProd, roadAdd, roadMod, flightFirst, flightProd, flightAdd, flightMod, K);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int N;
        from_stream(N);
        int roadFirst;
        from_stream(roadFirst);
        int roadProd;
        from_stream(roadProd);
        int roadAdd;
        from_stream(roadAdd);
        int roadMod;
        from_stream(roadMod);
        int flightFirst;
        from_stream(flightFirst);
        int flightProd;
        from_stream(flightProd);
        int flightAdd;
        from_stream(flightAdd);
        int flightMod;
        from_stream(flightMod);
        int K;
        from_stream(K);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, roadFirst, roadProd, roadAdd, roadMod, flightFirst, flightProd, flightAdd, flightMod, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1407748857;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "RoadOrFlightHard (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
