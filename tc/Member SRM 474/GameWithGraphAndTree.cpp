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
#include <string>
using namespace std;
#define N 14
#define MOD 1000000007
int dp[N][N][1<<N], n;
std::vector<string> graph, tree;
int visited[N+1];

using namespace std;
class GameWithGraphAndTree {
    public:
    void dfs(int index){
        std::vector<int> sons;
        visited[index] = 1;
        for(int i=0; i<n; ++i){
            if(visited[i]) continue;
            if(tree[index][i]=='N') continue;
            dfs(i);
            sons.push_back(i);
        }
        for(int i=0; i<n; ++i){
            dp[index][i][1<<i] = 1;
        }
        long long inner[2][1<<n];
        for(int p=0; p<n; ++p){
            memset(inner, 0, sizeof(inner));
            inner[0][1<<p] = 1;
            int sons_num = sons.size();
            for(int k=0; k<sons_num; ++k){
                memset(inner[(k+1)&1], 0, sizeof(inner[0][0]) * (1<<n));
                int son=sons[k];
                for(int exist=0; exist<(1<<n); exist++){
                    if(inner[k&1][exist] == 0) continue;
                    for(int j=0; j<n; ++j){
                        if(graph[p][j] == 'N') continue;
                        int reversed = ~exist & ((1<<n)-1);
                        for(int mask=reversed; mask>0; mask=(mask-1)&reversed){
                            if(dp[son][j][mask] == 0) continue;
                            inner[(k+1)&1][exist|mask]+=(inner[k&1][exist]*dp[son][j][mask])%MOD;
                            inner[(k+1)&1][exist|mask] %= MOD;
                        }
                    }
                }
            }
            for(int temp=0; temp<(1<<n); ++temp){
                dp[index][p][temp] = inner[sons_num&1][temp];
            }
        }
    }
    int calc(vector<string> G, vector<string> T) {
        graph = G;
        tree = T;
        n = tree.size();
        int ans = 0;
        memset(dp, 0, sizeof(dp));
        memset(visited, 0, sizeof(visited));
        dfs(0);
        for(int i=0; i<n; ++i){
            ans = (ans + dp[0][i][(1<<n)-1])%MOD;
        }
        return ans;
    }
};

// CUT begin
ifstream data("GameWithGraphAndTree.sample");

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

bool do_test(vector<string> graph, vector<string> tree, int __expected) {
    time_t startClock = clock();
    GameWithGraphAndTree *instance = new GameWithGraphAndTree();
    int __result = instance->calc(graph, tree);
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
        vector<string> graph;
        from_stream(graph);
        vector<string> tree;
        from_stream(tree);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(graph, tree, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1407720697;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GameWithGraphAndTree (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
