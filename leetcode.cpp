/*
 * leetcode.cpp
 * Copyright (C) 2014 zhao
 *
 * Distributed under terms of the MIT license.
 */
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
class Solution {
public:
    #define LEN 100010
    char *ptn, *text;
    int pi[LEN];
    int z[LEN];
    int R[50];
    int Nj[LEN], Lapo[LEN], L[LEN];
    int len_ptn, len_text;
    void compute_prefix(char *str, int len){
        if(len <= 0) return;
        memset(pi, 0, sizeof(pi));
        pi[0] = 0;
        int k = 0;
        for (int i = 1; i < len; ++i)
        {
            while(k > 0 && str[k] != str[i]) k = pi[k - 1];
            if(str[k] == str[i]) k += 1;
            if(str[k] == str[i + 1]){
                pi[i] = pi[k];
            }
            else
            {
                pi[i] = k;
            }
        }

    }

    char *kmp_matcher(char *text, int len_text, char *ptn, int len_ptn){
        int q = 0;
        for (int i = 0; i < len_text; ++i)
        {
            while(q > 0 && ptn[q] != text[i]) q = pi[q - 1];
            if(ptn[q] == text[i]) q += 1;
            if(q == len_ptn){
                return text + i - len_ptn + 1;
            }
        }
        return NULL;
    }

    char *strStr2(char *haystack, char *needle) {
            ptn = needle;
            text = haystack;
            if(strlen(ptn) == 0) return text;
            if(strlen(text) == 0) return NULL;
            compute_prefix(ptn, strlen(ptn));
            return kmp_matcher(text, strlen(text), ptn, strlen(ptn));

    }

    char *strStr3(char *haystack, char *needle) {
        if(!(*needle)) return haystack;
        char *current = haystack, *matched = needle;
        while(*current){
            matched = needle;
            char *start = current;
            while((*current) && (*matched) && (*current) == (*matched)){
                current++;
                matched++;
            }
            if(!(*matched)){
                return start;
            }
            if(!*current){
                return NULL;
            }
            current = start + 1;
        }
        return NULL;
    }

    void compute_z(char *str){
        int len = strlen(str);
        memset(z, 0, sizeof(z));
        int l = -1, r = 0;
        for(int i = 1; i < len; ++i){
            if(i >= r){
                int current = 0;
                while(str[current] == str[i + current]){
                    current++;
                }
                z[i] = current;
                l = i;
                r = i + current;
            }
            else{
                int start_index = i - l;
                if(i + z[start_index] < r){
                    z[i] = z[start_index];
                }
                else{
                    while(str[r - i] == str[r]) r++;
                    l = i;
                    z[i] = r - l;
                }
            }
        }
    }

    void compute_bad(char *str){
        memset(R, 0, sizeof(R));
        for(int i = 0; i < len_ptn; ++i){
            R[str[i] - 'a'] = i;
        }
    }
    void compute_Nj(char *str){
        reverse(str, str + len_ptn);
        compute_z(str);
        reverse(str, str + len_ptn);
        for (int i = 0; i < len_ptn; ++i)
        {
            Nj[i] = z[len_ptn - 1 - i];
            //printf("%d ", Nj[i]);
        }
        //putchar('\n');
    }
    void compute_Lapo(char *str){
        memset(Lapo, 0xff, sizeof(Lapo));
        for(int i = 0; i < len_ptn; ++i){
            if(Nj[i]) Lapo[len_ptn - Nj[i]] = i;
        }
        for(int i = len_ptn - 2; i >= 0; --i){
            if(str[i] != str[len_ptn - 1]){
                Lapo[len_ptn] = i;
                break;
            }
        }
    }

    void compute_L(){
        for(int i = 0; i < len_ptn; ++i){
            if(Nj[i] == i + 1){
                L[len_ptn - 1 - i] = Nj[i];
            }
        }
        for(int i = len_ptn - 1; i > 0;){
            if(L[i]){
                int next = i - 1;
                while(next > 0 && L[next] == 0){
                    L[next] = L[i];
                    next--;
                }
                i = next;
            }
            else{
                i--;
            }
        }
        //for (int i = 0; i < len_ptn; ++i)
        //{
            //printf("%d ", L[i]);
        //}
        //putchar('\n');
    }
    char* run_BM(){
        int ans = 0;
        int k = len_ptn - 1;
        while(k < len_text){
            int i = len_ptn - 1, h = k;
            while(i >= 0 && ptn[i] == text[h]){
                i--;
                h--;
            }
            if(i < 0){
                return text + h + 1;
            }
            else{
                int delta_R = max(1, i - R[text[h] - 'a']);
                int delta_Lapo;
                if(Lapo[i + 1] >= 0){
                    delta_Lapo = len_ptn - 1 - Lapo[i + 1];
                }
                else{
                    delta_Lapo = len_ptn - L[i + 1];
                }
                k += max(delta_R, delta_Lapo);
            }
        }
        return NULL;
    }

    char *strStr(char *haystack, char *needle) {
        ptn = needle;
        text = haystack;
        if(strlen(ptn) == 0) return text;
        if(strlen(text) == 0) return NULL;
        len_ptn = strlen(ptn);
        len_text = strlen(text);
        compute_bad(ptn);
        compute_Nj(ptn);
        compute_Lapo(ptn);
        compute_L();
        return run_BM();
    }
};

int main(){
    Solution *t = new Solution();
    char text[] = "mississippi", ptn[] = "zissi";
    printf("%s\n", t->strStr3(text, ptn));
    return 0;
}
