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
#define MOD 1000000007
#define max_width 6600
#define W 8
#define H 105
int cached[105][9][max_width];
int get_value[max_width][9];
int set_value[max_width][8][3];
int power3[9];
int width, height;
int P[1<<W];
int dp[H][(1<<W)+1][(1<<W)+1];

class DengklekPaintingSquares {
    public:
    int numSolutions2(int N, int M) {
        width = M;
        height = N;
        power3[0] = 1;
        for(int i=1; i<=8; ++i) power3[i] = power3[i-1]*3;
        int MASK = (power3[width]-1);
        for(int i=0; i<=MASK; ++i){
            int current = i;
            for(int j=0; j<8; ++j){
                get_value[i][j] = current % 3;
                current/=3;
            }
        }
        for(int i=0; i<=MASK; ++i){
            for(int index=0; index<8; index++){
                for(int next=0; next<3; next++){
                    set_value[i][index][next] = i + (next - get_value[i][index]) * power3[index];
                }
            }
        }
        cached[0][0][MASK] = 1;
        for(int i=0; i<height; ++i){
            for(int j=0; j<width; ++j){
                for(int mask=0; mask<=MASK; ++mask){
                    // leave it as it is
                    if(get_value[mask][j] != 1){
                        cached[i][j+1][set_value[mask][j][2]] += cached[i][j][mask];
                        cached[i][j+1][set_value[mask][j][2]] %= MOD;
                    }
                    // color it
                    if(get_value[mask][j] != 0){
                        int new_mask = set_value[mask][j][0];
                        if(get_value[mask][j] != 2){
                            new_mask = set_value[new_mask][j][1 - get_value[new_mask][j]];
                        }
                        if( j>0 && get_value[mask][j-1]!=2){
                            new_mask = set_value[new_mask][j-1][1-get_value[new_mask][j-1]];
                            new_mask = set_value[new_mask][j][1-get_value[new_mask][j]];
                        }
                        cached[i][j+1][new_mask] += cached[i][j][mask];
                        cached[i][j+1][new_mask] %= MOD;
                    }
                }
            }
            for(int mask=0; mask<=MASK; mask++){
                cached[i+1][0][mask] = cached[i][width][mask];
            }
        }
        int ans = 0;
        for(int mask=0; mask<=MASK; ++mask){
            bool is_valid = true;
            for(int index=0; index<8; index++){
                if(get_value[mask][index]==1){
                    is_valid=false;
                    break;
                }
            }
            if(is_valid && cached[height][0][mask]){
                ans = (ans + cached[height][0][mask]);
                ans%=MOD;
            }
        }
        return ans;
    }

    int numSolutions(int N, int M) {
        int MASK = (1<<M)-1;
        for(int i=0; i<=MASK; ++i) P[i] = ((i<<1) ^ (i>>1)) & i;
        dp[0][0][0] = 1;
        for(int i=0; i<N; ++i){
            for(int mask=0; mask<=MASK; mask++){
                int nx = mask ^ MASK;
                for(int px=mask; ;px=(px - 1)&mask){
                    for(int y=nx; ; y=(y - 1)&nx){
                        int z = y ^ px;
                        int pz = P[z] ^ px;
                        dp[i+1][z][pz]=(dp[i+1][z][pz] + dp[i][mask][px])%MOD;
                        if(y == 0) break;
                    }
                    if(px == 0) break;
                }
            }
        }
        int ans = 0;
        for(int i=0; i<=MASK; ++i){
            ans=(ans + dp[N][i][0])%MOD;
        }
        return ans;
    }
};

// CUT begin
ifstream data("DengklekPaintingSquares.sample");

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

bool do_test(int N, int M, int __expected) {
    time_t startClock = clock();
    DengklekPaintingSquares *instance = new DengklekPaintingSquares();
    int __result = instance->numSolutions(N, M);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1407201660;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DengklekPaintingSquares (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
