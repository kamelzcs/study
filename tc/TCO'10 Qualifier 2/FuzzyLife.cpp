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

class FuzzyLife {
    public:
    int a[100][100];
    bool used[100][100];
    int W, H;
    bool live(int x, int y){
        if(x <= 0 || x >= H - 1){
            return false;
        }
        if(y <= 0 || y >= W - 1){
            return false;
        }
        int lives = 0;
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(i == 1 && j == 1){
                    continue;
                }
                if(a[x - 1 + i][y - 1 + j] == 1) lives++;
            }
        }
        if(a[x][y] == 1){
            if(lives >= 2 && lives <= 3) return true;
        }
        else if(a[x][y] == 0){
            if(lives == 3) return true;
        }
        return false;
    }
    int survivingCells(vector<string> grid) {
        memset(a, 0, sizeof(a));
        memset(used, false, sizeof(used));
        W = grid[0].size();
        H = grid.size();
        for(int i = 0; i < H; ++i){
            for(int j = 0; j < W; ++j){
                if(grid[i][j] == '0') a[i + 2][j + 2] = 0;
                else if(grid[i][j] == '1') a[i + 2][j + 2] = 1;
                else a[i + 2][j + 2] = 2;
            }
        }
        W += 4;
        H += 4;
        int ans = 0;
        for(int i = 0; i < H; ++i){
            for(int j = 0; j < W; ++j){
                if(a[i][j] == 2){
                    a[i][j] = 0;
                    int temp = 0, temp1 = 0;
                    for(int l = 0; l < 3; ++l){
                        for(int k = 0; k < 3; ++k){
                            if(live(i - 1 + l, j - 1 + k)){
                                temp++;
                            }
                        }
                    }
                    a[i][j] = 1;
                    for(int l = 0; l < 3; ++l){
                        for(int k = 0; k < 3; ++k){
                            if(live(i - 1 + l, j - 1 + k)){
                                temp1++;
                            }
                        }
                    }
                    ans += max(temp, temp1);
                    a[i][j] = 2;
                    for(int l = 0; l < 3; ++l){
                        for(int k = 0; k < 3; ++k){
                            used[i - 1 + l][j - 1 + k] = true;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < H; ++i){
            for(int j = 0; j < W; ++j){
                if(live(i, j) && !used[i][j]){
                    ans++;
                }
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("FuzzyLife.sample");

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

bool do_test(vector<string> grid, int __expected) {
    time_t startClock = clock();
    FuzzyLife *instance = new FuzzyLife();
    int __result = instance->survivingCells(grid);
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
        vector<string> grid;
        from_stream(grid);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1431394927;
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
        cout << "FuzzyLife (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
