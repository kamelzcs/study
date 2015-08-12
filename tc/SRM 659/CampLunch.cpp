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

void CK(int &base, int delta){
    base = (base + delta) % 1000000007;
}

class CampLunch {
    public:
    int dp[400][1<<16];
    int count(int N, int M, vector<string> a) {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(int i = 0; i < N*M; ++i){
            for(int mask = 0; mask < (1<<M); ++mask){
                if(!dp[i][mask]) continue;
                int p = a[i / M][i % M] - 'A';
                if(mask & (1<<p)){
                    CK(dp[i + 1][mask ^ (1<<p)] , dp[i][mask]);
                    continue;
                }
                //plan 1
                if((i%M) != M - 1){
                    int p2 = a[i / M][(i % M) + 1] - 'A';
                    if(!(mask & (1<<p2))){
                        CK(dp[i + 2][mask] , dp[i][mask]);
                    }
                }
                //plan 2
                CK(dp[i + 1][mask | (1<<p)] , dp[i][mask]);
                //plan 3
                CK(dp[i + 1][mask] , dp[i][mask]);
            }
        }
        return dp[N * M][0];
    }
};

// CUT begin
ifstream data("CampLunch.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool do_test(int N, int M, vector<string> a, int __expected) {
    time_t startClock = clock();
    CampLunch *instance = new CampLunch();
    int __result = instance->count(N, M, a);
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
        int M;
        from_stream(M);
        vector<string> a;
        from_stream(a);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1431651773;
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
        cout << "CampLunch (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
