#include<stdio.h>
#include<algorithm>
#include<map>
#include<string.h>
#include<string>
#include<assert.h>
#include<iostream>
#define SIZE 100010
#define ALPHA 27
int *e;
int last_non;
int *dummy;

typedef struct node node;
struct node{
    int start;
    int *end;
    int leaf_index;
    node* suffix_link, *parent;
    node* child[ALPHA];
    node(){
    }
    node(int s, int *t, node* back, node* p, int sindex){
        start = s;
        end = t;
        suffix_link = back;
        parent = p;
        leaf_index = sindex;
    }
    node(const node& clone):start(clone.start), end(clone.end), suffix_link(clone.suffix_link), leaf_index(clone.leaf_index), parent(clone.parent){
    }
};

int used_num = 0;
node node_array[200010];
node *get_next(int s, int *t, node* back, node* p, int sindex){
    node *ans = node_array + used_num++;
    ans->start = s;
    ans->end = t;
    ans->suffix_link = back;
    ans->parent = p;
    ans->leaf_index = sindex;
    memset(ans->child, 0, sizeof(ans->child));
    return ans;
}
node *pre, *root, *parent, *current;
int ans;
char str[2 * SIZE], pattern[SIZE];
int len, remain_len, base, pattern_len;
int matched;
char base_char;

void init(){
    e = new int(0);
    dummy = new int(-1);
    used_num = 0;
    root = get_next(-1, dummy, NULL, NULL, -100);
    ans = 0;
    matched = 0;
    base_char = 'a';
}

int edge_len(node* now){
    return *now->end - now->start + 1;
}


int to_int(char temp){
    return temp - base_char;
}

void walk_down(node** now, int &remain, int &start){
    while(remain){
        node* next = (*now)->child[to_int(str[start])];
        int length = edge_len(next);
        if(length > remain) break;
        remain -= length;
        start += length;
        *now = next;
    }
}

void print(node* now){
    printf("started %d\n", now->leaf_index);
    printf("%d %d\n", now->start, *now->end);
    for(int index = 0; index < ALPHA; ++index){
        if(now->child[index]){
            printf("%c\n", base_char + index);
            print(now->child[index]);
        }
    }
    printf("finished %d\n", now->leaf_index);
}

void build(){
    //build s[0];
    root->child[to_int(str[0])] = get_next(0, e, NULL, root, 0);
    //update s[j - 1, i - 1] to s[j, i - 1]
    //build s[j, i] from s[j, i - 1]
    //current is at s[j - 1, i - 1] (leaf node or the internal node)
    //for the s[ last_non + 1, i], current should be s[ last_non, i - 1]
    current = root->child[to_int(str[0])];
    //last_non is the last non extension in the s[ j - 1, i - 1]
    //remain_len is the left part in current node
    //base is the index in the str to start match
    int last_non = 0, remain_len = 0, base = 0;
    for(int i = 1; i <= len; ++i){
        pre = NULL;
        current = root;
        base = last_non;
        remain_len = i - last_non;
        walk_down(&current, remain_len, base);
        for(int j = last_non + 1; j <= i; ++j){
            //explict extentions for last_non + 1...i
            //update s[ j - 1, i - 1] to s[j, i - 1]
            if(current->leaf_index >= 0){
                //now at the leaf, should go up to the internal node
                base = current->start;
                remain_len = edge_len(current);
                current = current->parent;
            }
            if(current == root){
                base = j;
                remain_len = i - j;
            }
            else{
                current = current->suffix_link;
            }
            walk_down(&current, remain_len, base);
            if(pre != NULL){
                pre->suffix_link = current;
            }
            if(remain_len == 0){
                if(current->child[to_int(str[i])] == NULL){
                    //rule 2
                    //puts("rule 2");
                    //printf("j %d, str[j] %c, current->leafindex %d current->start %d\n", j, str[j], current->leaf_index, current->start);
                    node *new_node = get_next(i, e, NULL, current, j);
                    current->child[to_int(str[i])] = new_node;
                    pre = NULL;
                    last_non = j;
                }
                else{
                    //rule 3
                    //puts("rule 3");
                    pre = NULL;
                    break;
                }
            }
            else{
                node *next = current->child[to_int(str[base])];
                //printf("remain_len %d\n", remain_len);
                if(str[next->start + remain_len] != str[i]){
                    //rule 2
                    //puts("split rule 2");
                    int *middle_end = new int(next->start + remain_len - 1);
                    //printf("next->start %d middle_end %d\n", next->start, *middle_end);
                    node *new_middle = get_next(next->start, middle_end, NULL, current, -1);
                    current->child[to_int(str[base])] = new_middle;
                    next->start = (*middle_end) + 1;
                    node *new_leaf = get_next(i, e, NULL, new_middle, j);
                    new_middle->child[to_int(str[i])] = new_leaf;
                    new_middle->child[to_int(str[next->start])] = next;
                    //printf("new_middle start %d end %d leaf_index %d\n", new_middle->start, *(new_middle->end), new_middle->leaf_index);
                    last_non = j;
                    if(pre != NULL){
                        pre->suffix_link = new_middle;
                    }
                    pre = new_middle;
                }
                else{
                    //rule 3
                    //puts("rule 3");
                    pre = NULL;
                    break;
                }
            }
        }
        //implict extentions for 0...last_non extensions
        (*e) = i;
    }
}

std::string combine(node* now){
    int start = now->start, end = *now->end;
    std::string temp = "";
    for(int i = start; i <= end; ++i){
        temp += str[i];
    }
    return temp;
}

void beautiful_print(node *now, std::string part){
    if(now->leaf_index >= 0){
        std::cout << part << std::endl;
        return;
    }
    else{
        for(int i = 0; i < ALPHA; ++i){
            if(now->child[i] == NULL) continue;
            std::string temp = part;
            node *next = now->child[i];
            temp += combine(next);
            beautiful_print(next, temp);
        }
    }
}

void find_next(node **now, int &remain_len, int &base, int index){
    if(remain_len == 0){
        if((*now)->child[to_int(pattern[index])] == NULL){
            if((*now) == root){
                matched=0;
            }
            else{
                matched--;
                (*now) = (*now)->suffix_link;
                find_next(now,remain_len, base, index);
            }
        }
        else{
            node *child = (*now)->child[to_int(pattern[index])];
            base = child->start;
            matched++;
            remain_len++;
            if(remain_len == edge_len(child)){
                remain_len = 0;
                base = child->start;
                (*now) = child;
            }
        }
    }
    else{
        node *child = (*now)->child[to_int(str[base])];
        if(str[child->start + remain_len] == pattern[index]){
            matched++;
            remain_len++;
            if(remain_len == edge_len(child)){
                remain_len = 0;
                base = child->start;
                (*now) = child;
            }
        }
        else{
            matched--;
            if((*now) == root){
                base = index - remain_len + 1;
                remain_len--;
                walk_down(now, remain_len, base);
                find_next(now,remain_len, base, index);
            }
            else{
                base = child->start;
                (*now) = (*now)->suffix_link;
                walk_down(now, remain_len, base);
                find_next(now,remain_len, base, index);
            }
        }
    }
}

void match(){
    //update from pattern[i - 1] to pattern[i]
    current = root;
    base = 0;
    remain_len = 0;
    for(int i = 0; i < pattern_len; ++i){
        find_next(&current, base, remain_len, i);
        ans = std::max(ans, matched);
        //printf("matched %d\n", matched);
    }
}

int main(){
    while(scanf("%s %s", str, pattern) != EOF){
        //scanf("%s %s", str, pattern);
        len = strlen(str);
        str[len] = '{';
        str[len + 1] = '\0';
        pattern_len = strlen(pattern);
        init();
        build();
        //puts("print tree-----------");
        //print(root);
        //puts("beautiful print tree-----------");
        //beautiful_print(root, "");
        match();
        printf("%d\n", ans);
    }
    return 0;
}
