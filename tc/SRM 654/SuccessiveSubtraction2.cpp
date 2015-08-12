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

class SuccessiveSubtraction2 {
    public:
    vector<int> a;
    int dp[2010][3][2];
    int dfs(int index, int open, int con){
        int &ret = dp[index][open][con];
        if(ret != -1){
            return ret;
        }
        ret = 0;
        if(index >= a.size()){
            return ret;
        }
        if(open < 2){
            // use a[index]
            if(con == 0){
                ret = max(ret, dfs(index + 1, open + 1, 1) + a[index]);
            }
            else{
                ret = max(ret, dfs(index + 1, open, 1) + a[index]);
            }
            // not user a[index]
            ret = max(ret, dfs(index + 1, open, 0));
        }
        else{
            if(con == 0){
                //can not user a[index]
                ret = max(ret, dfs(index + 1, open, 0));
            }
            else{
                //use a[index]
                ret = max(ret, dfs(index + 1, open, 1) + a[index]);
                // not user a[index]
                ret = max(ret, dfs(index + 1, open, 0));
            }
        }
        return ret;
    }
    vector<int> calc(vector<int> _a, vector<int> p, vector<int> v) {
        vector<int> ans;
        a = _a;
        for(int i = 0; i < p.size(); ++i){
            a[p[i]] = v[i];
            memset(dp, -1, sizeof(dp));
            int base = a[0];
            for(int j = 1; j < a.size(); ++j){
                base -= a[j];
            }
            ans.push_back(dfs(2, 0, 0) * 2 + base);
        }
        return ans;
    }
};

// CUT begin
ifstream data("SuccessiveSubtraction2.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> a, vector<int> p, vector<int> v, vector<int> __expected) {
    time_t startClock = clock();
    SuccessiveSubtraction2 *instance = new SuccessiveSubtraction2();
    vector<int> __result = instance->calc(a, p, v);
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
        vector<int> a;
        from_stream(a);
        vector<int> p;
        from_stream(p);
        vector<int> v;
        from_stream(v);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, p, v, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1429752098;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SuccessiveSubtraction2 (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
