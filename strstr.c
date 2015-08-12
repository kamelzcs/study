/*
 * strstr.c
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

int match(char *s, char *t, int len){
    for(int i = 0; i < len; ++i){
        if(s[i] != t[i]){
            return 0;
        }
    }
    return 1;
}

int strStr(char *haystack, char *needle) {
    if(!haystack){
        if(!needle){
            return 0;
        }
        return -1;
    }
    if(!needle){
        return 0;
    }
    int len_haystack = strlen(haystack), len_need = strlen(needle);
    for(int i = 0; i + len_need <= len_haystack; ++i){
        if(match(haystack + i, needle, len_need)){
            return i;
        }
    }
    return -1;
}


