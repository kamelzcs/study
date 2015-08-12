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
#define W 15
#define H 15
int cached[1<<W];
int cover[1<<W], content[H];
int width, height;
int MASK;

using namespace std;

class InformFriends {
    public:
    int maximumGroups(vector<string> friends) {
        memset(cached, 0, sizeof(cached));
        memset(cover, 0, sizeof(cover));
        memset(content, 0, sizeof(content));
        width = friends[0].size(), height=friends.size();
        MASK = (1<<width) - 1;
        for(int i=0; i<height; ++i){
            for(int j=0; j<width; ++j){
                if(j==i || friends[i][j]=='Y') content[i]|=(1<<j);
            }
        }
        for(int i=0; i<=MASK; ++i){
            int temp=0;
            for(int j=0; j<height; ++j){
                if(i&(1<<j)) temp|=content[j];
            }
            cover[i] = (temp==MASK);
        }
        for(int mask=0; mask<=MASK; ++mask){
            for(int j=mask; j>0; j=(j-1)&mask){
                if(cover[j]) cached[mask] = max(cached[mask], cached[mask^j]+1);
            }
        }
        return cached[MASK];
    }
};

// CUT begin
ifstream data("InformFriends.sample");

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

bool do_test(vector<string> friends, int __expected) {
    time_t startClock = clock();
    InformFriends *instance = new InformFriends();
    int __result = instance->maximumGroups(friends);
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
        vector<string> friends;
        from_stream(friends);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(friends, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1407374759;
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
        cout << "InformFriends (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
