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
#include <queue>

using namespace std;

int visited[2010][2010];
int offset = 1000;
int dx[]={0, -1, 0, 1};
int dy[]={-1, 0, 1, 0};
int wall[2010][2010];
class TheGridDivTwo {
    public:
    int find(vector<int> x, vector<int> y, int k) {
        memset(visited, 0, sizeof(visited));
        memset(wall, 0, sizeof(wall));
        for(int i = 0; i < x.size(); ++i){
            wall[x[i] + offset][y[i] + offset] = 1;
        }
        int ans = 0;
        queue<int> Q;
        Q.push(offset); Q.push(offset); Q.push(0);
        visited[offset][offset] = 1;
        while(!Q.empty()){
            int x = Q.front(); Q.pop();
            int y = Q.front(); Q.pop();
            int step = Q.front(); Q.pop();
            if(step >= k){
                continue;
            }
            for(int d = 0; d < 4; ++d){
                int nxt_x = x + dx[d], nxt_y = y + dy[d], nxt_step = step + 1;
                if(visited[nxt_x][nxt_y] || wall[nxt_x][nxt_y]){
                    continue;
                }
                ans = max(ans, nxt_x - offset);
                visited[nxt_x][nxt_y] = 1;
                Q.push(nxt_x); Q.push(nxt_y); Q.push(nxt_step);
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("TheGridDivTwo.sample");

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

bool do_test(vector<int> x, vector<int> y, int k, int __expected) {
    time_t startClock = clock();
    TheGridDivTwo *instance = new TheGridDivTwo();
    int __result = instance->find(x, y, k);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1434504761;
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
        cout << "TheGridDivTwo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
