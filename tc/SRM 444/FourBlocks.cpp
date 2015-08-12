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
#define W 10
#define H 25
int dp[H+1][W+1][(1<<(W+1))];
int width, height;
std::vector<string> vs;

class FourBlocks {
    public:
    /*
     *calculate(x,y,mask): the current position is x,y, and the x-1, y-1 is not the left-top of 2*2 and x,y,mask is a valid state
     * O(width * height * 2^(width))
     */
    int maxScore(vector<string> grid) {
        width = grid.size(), height = grid[0].size();
        memset(dp, 0xff, sizeof(dp));
        dp[0][0][0] = 0;
        int MASK = (1<<(width + 1)) - 1;
        for(int x=0; x<height; ++x){
            for(int y=0; y<width; ++y){
                for(int mask=0; mask<=MASK; ++mask){
                    if(dp[x][y][mask] == -1) continue;
                    if(mask&(1<<y)){
                        dp[x][y+2][mask&(~(1<<y))] = max(dp[x][y+2][mask&(~(1<<y))], dp[x][y][mask]);
                        continue;
                    }
                    // do nothing
                    dp[x][y+1][mask] = max(dp[x][y+1][mask], dp[x][y][mask]);
                    // try to add a 2*2
                    if(x<=height-2 && y<=width-2 && grid[y][x]!='1' && grid[y+1][x]!='1' && grid[y][x+1]!='1' && grid[y+1][x+1]!='1' && (mask&(1<<(y+1)))==0){
                        dp[x][y+2][mask|(1<<y)] = max(dp[x][y+2][mask|(1<<y)], dp[x][y][mask]+1);
                    }
                }
            }
            for(int mask=0; mask<(1<<(width)); ++mask){
                dp[x+1][0][mask] = max(dp[x+1][0][mask], dp[x][width][mask]);
            }
        }
        return width*height + 12*dp[height][0][0];
    }

    /*
     *calculate(x,y,mask): the current position is x,y, and the x-1, y-1 is not the left-top of 2*2 and x,y,mask is a valid state
     * O(width * height * 2^width)
     */
    int calculate(int x, int y, int mask){
        int& res = dp[x][y][mask];
        if(res != -1) return res;
        if(y == width) return res=calculate(x+1,0,mask);
        if(x == height) return res=0;
        if(mask&(1<<y)) return calculate(x, y+2, mask&(~(1<<y))&(~(1<<(y+1))));

        // do nothing
        res = calculate(x, y+1, mask&(~(1<<y)));
        if(x<=height-2 && y<=width-2 && vs[y][x]!='1' && vs[y+1][x]!='1' && vs[y][x+1]!='1' && vs[y+1][x+1]!='1' && (mask&(1<<(y+1)))==0)
        {
            res = max(res, calculate(x, y+2, mask | (1<<y)) + 1);
        }
        return res;
    }

    int maxScore2(vector<string> grid) {
        width = grid.size(), height = grid[0].size();
        memset(dp, 0xff, sizeof(dp));
        vs = grid;
        return width * height + 12 * calculate(0,0,0);
    }
};

// CUT begin
ifstream data("FourBlocks.sample");

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
    FourBlocks *instance = new FourBlocks();
    int __result = instance->maxScore(grid);
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
        int T = time(NULL) - 1407286972;
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
        cout << "FourBlocks (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
