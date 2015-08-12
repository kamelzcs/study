#include<stdio.h>
#include<string.h>
#define LEN 10011
int pi[LEN];
char ptn[LEN], text[LEN * 100];
void compute_prefix(char *str, int len){
    if(len <= 0) return;
    memset(pi, 0, sizeof(pi));
    pi[0] = 0;
    int k = 0;
    for (int i = 1; i < len; ++i)
    {
        while(k > 0 && str[k] != str[i]) k = pi[k - 1];
        if(str[k] == str[i]) k += 1;
        if(str[k] != str[i + 1]) pi[i] = k;
        else pi[i] = pi[k - 1];
    }
}
int kmp_matcher(char *text, int len_text, char *ptn, int len_ptn){
    int ans = 0;
    int q = 0;
    for (int i = 0; i < len_text; ++i)
    {
        while(q > 0 && ptn[q] != text[i]) q = pi[q - 1];
        if(ptn[q] == text[i]) q += 1;
        if(q == len_ptn){
            ans += 1;
            q = pi[q - 1];
        }
    }
    return ans;
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    while(n--){
        scanf("%s", ptn);
        scanf("%s", text);
        compute_prefix(ptn, strlen(ptn));
        printf("%d\n", kmp_matcher(text, strlen(text), ptn, strlen(ptn)));
    }
    return 0;
}
