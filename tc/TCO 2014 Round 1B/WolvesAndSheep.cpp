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

class WolvesAndSheep {
    public:
    int R, C;
    vector<string> field;
    bool valid(int mask){
        vector<int> blocks;
        blocks.push_back(-1);
        for(int i = 0; i < R; ++i){
            if((1<<i) & mask){
                blocks.push_back(i);
            }
        }
        blocks.push_back(R - 1);
        for(int col = 0; col < C; ++col){
            int pos = 0;
            while(pos < blocks.size() - 1){
                bool wolf = false, sheep = false;
                for(int index = blocks[pos] + 1; index <= blocks[pos + 1]; ++index){
                    if(field[index][col] == 'W'){
                        if(sheep){
                            return false;
                        }
                        wolf = true;
                    }
                    else if(field[index][col] == 'S'){
                        if(wolf){
                            return false;
                        }
                        sheep = true;
                    }
                }
                pos++;
            }
        }
        return true;
    }
    vector<string> trans(int mask){
        //cout<<mask<<endl;
        vector<int> blocks;
        vector<string> ans;
        blocks.push_back(-1);
        for(int i = 0; i < R; ++i){
            if((1<<i) & mask){
                blocks.push_back(i);
                ans.push_back("");
            }
        }
        ans.push_back("");
        blocks.push_back(R - 1);
        for(int col = 0; col < C; ++col){
            int pos = 0;
            while(pos < blocks.size() - 1){
                char temp = '.';
                for(int index = blocks[pos] + 1; index <= blocks[pos + 1]; ++index){
                    if(field[index][col] != '.'){
                        temp = field[index][col];
                    }
                }
                ans[pos].push_back(temp);
                pos++;
            }
        }
        return ans;
    }
    bool can_cut(vector<string> transformed, int start, int end){
        for(int i = 0; i < transformed.size(); ++i){
            bool wolf = false, sheep = false;
            for(int j = start; j <= end; ++j){
                if(transformed[i][j] == 'W'){
                    if(sheep){
                        return false;
                    }
                    wolf = true;
                }
                else if(transformed[i][j] == 'S'){
                    if(wolf){
                        return false;
                    }
                    sheep = true;
                }
            }
        }
        return true;
    }
    int calc(vector<string> transformed, int col){
        if(col >= transformed[0].size()){
            return 0;
        }
        for(int pos = (int)transformed[0].size() - 1; pos >= col; --pos){
            int delta = 1;
            if(pos == (int)transformed[0].size() - 1){
                delta = 0;
            }
            if(can_cut(transformed, col, pos)){
                return calc(transformed, pos + 1) + delta;
            }
        }
        return 100000;
    }
    int getmin(vector<string> _field) {
        field = _field;
        R = field.size(), C = field[0].size();
        int ans = R + C - 2;
        for(int mask = 0; mask < (1<<(R - 1)); ++mask){
            if(!valid(mask)){
                continue;
            }
            vector<string> transformed = trans(mask);
            int temp = calc(transformed, 0) + __builtin_popcount(mask);
            if(temp < ans){
                ans = temp;
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("WolvesAndSheep.sample");

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

bool do_test(vector<string> field, int __expected) {
    time_t startClock = clock();
    WolvesAndSheep *instance = new WolvesAndSheep();
    int __result = instance->getmin(field);
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
        vector<string> field;
        from_stream(field);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1431997567;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "WolvesAndSheep (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
