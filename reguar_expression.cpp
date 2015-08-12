#include<string>
#include<memory.h>
using namespace std;

class Solution {
public:
    int len_s, len_p;
    int match[110][110];
    bool isMatch(string s, string p) {
        len_s = s.size(), len_p = p.size();
        memset(match, 0, sizeof(match));
        match[0][0] = 1;
        for(int iter_p = 1; iter_p <= len_p; ++iter_p){
            for(int iter_s = 0; iter_s <= len_s; ++iter_s){
                char char_p = p[iter_p - 1];
                if(char_p == '.'){
                    if(iter_s){
                        match[iter_p][iter_s] = match[iter_p - 1][iter_s - 1];
                    }
                }
                else if(char_p == '*'){
                    if(iter_p == 1){
                        return false;
                    }
                    //zero pre
                    match[iter_p][iter_s] = match[iter_p - 2][iter_s];
                    //one pre
                    match[iter_p][iter_s] |= match[iter_p - 1][iter_s];
                    //more pre
                    if(iter_s){
                        if(p[iter_p - 2] == s[iter_s - 1] || p[iter_p - 2] == '.'){
                            match[iter_p][iter_s] |= match[iter_p][iter_s - 1];
                        }
                    }
                }
                else{
                    if(iter_s && p[iter_p - 1] == s[iter_s - 1]){
                        match[iter_p][iter_s] = match[iter_p - 1][iter_s - 1];
                    }
                }
            }
        }
        return match[len_p][len_s];
    }
};
