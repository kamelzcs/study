/*
 * length_of_last_word.c
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>

int lengthOfLastWord(char *s) {
    if(!s){
        return 0;
    }
    int length = 0;
    while(s[length]){
        length++;
    }
    int end = length - 1;
    while(end >= 0 && s[end] == ' '){
        end--;
    }
    if(end < 0){
        return 0;
    }
    int start = end - 1;
    while(start >= 0 && s[start] != ' '){
        start--;
    }
    return end - start;
}

int main(){
    return 0;
}


