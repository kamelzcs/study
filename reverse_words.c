#include<stdio.h>

void reverse(char *s, int start, int end){
    while(start < end){
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

void reverseWords(char *s) {
    if(!s){
        return;
    }
    int len = 0, current = 0;
    while(s[current] == ' '){
        current++;
    }
    while(s[current]){
        s[len++] = s[current++];
    }
    if(len == 0){
        s[len] = '\0';
        return;
    }
    while(s[len - 1] == ' '){
        len--;
    }
    s[len] = '\0';
    int ans_len = 0;
    current = 0;
    int nxt = 0;
    while(1){
        while(s[nxt] && s[nxt] != ' '){
            s[ans_len++] = s[nxt++];
        }
        if(s[nxt] == 0){
            break;
        }
        s[ans_len++] = ' ';
        current = nxt;
        while(s[current] == ' '){
            current++;
        }
        nxt = current;
    }
    s[ans_len] = '\0';
    current = 0, nxt = 0;
    while(1){
        while(s[nxt] && s[nxt] != ' '){
            nxt++;
        }
        reverse(s, current, nxt - 1);
        current = nxt + 1;
        nxt = current;
        if(s[nxt] == 0){
            break;
        }
    }
    reverse(s, 0, ans_len - 1);
}

int main(){
    char str2[100] = " a  b";
    reverseWords(str2);
    puts(str2);
}
