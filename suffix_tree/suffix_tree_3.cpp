#include<stdio.h>
#include<algorithm>
#include<map>
#include<string.h>
#include<assert.h>
#define SIZE 100010
int *e;
int last_non;
int *dummy;

typedef struct node node;
struct node{
    int start;
    int *end;
    int leaf_index;
    node* suffix_link, *parent;
    std::map<char, node*>child;
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
node node_array[SIZE * 7];
node *get_next(int s, int *t, node* back, node* p, int sindex){
    node *ans = node_array + used_num++;
    ans->start = s;
    ans->end = t;
    ans->suffix_link = back;
    ans->parent = p;
    ans->leaf_index = sindex;
    return ans;
}
node *pre, *root, *parent, *current;
int ans;
char str[SIZE], pattern[SIZE];
int len, remain_len, base, pattern_len;

void init(){
    e = new int(0);
    dummy = new int(-1);
    root = get_next(-1, dummy, NULL, NULL, -100);
    ans = 0;
}

int edge_len(node* now){
    return *now->end - now->start + 1;
}

void walk_down(node** now, int &remain, int &start){
    while(remain){
        node* next = (*now)->child[str[start]];
        int length = edge_len(next);
        if(length > remain) break;
        remain -= length;
        start += length;
        *now = next;
    }
}

void find_next(node **now, int &matched, int &remain, int index){
    if(remain == 0){
        char next_char = pattern[index];
        if((*now)->child.find(next_char) == (*now)->child.end()){
            matched--;
            if((*now) == root){
                matched = 0;
            }
            else{
                (*now) = (*now)->suffix_link;
                find_next(now, matched, remain, index);
            }
        }
        else{
            node *next = (*now)->child[next_char];
            remain++;
            matched++;
            if(edge_len(next) == remain){
                (*now) = next;
                remain = 0;
            }
        }
    }
    else{
        int start = index - remain;
        node *next = (*now)->child[pattern[start]];
        if(pattern[index] == str[next->start + remain]){
            remain++;
            matched++;
            if(edge_len(next) == remain){
                (*now) = next;
                remain = 0;
            }
        }
        else{
            matched--;
            if((*now) == root){
                int start = index - remain;
                node *next = (*now)->child[pattern[start]];
                start = next->start + 1;
                remain--;
                walk_down(now, remain, start);
                find_next(now, matched, remain, index);
            }
            else{
                int start = (next)->start;
                (*now) = (*now)->suffix_link;
                //printf("%d %d\n", remain, start);
                walk_down(now, remain, start);
                //printf("%d %d\n", remain, start);
                find_next(now, matched, remain, index);
            }
        }
    }
}

void build(){
    //build s[0]
    node *first = get_next(0, e, NULL, root, 0);
    root->child[str[0]] = first;
    current = root;
    base = 0;
    last_non = 0;
    remain_len = 0;
    pre = NULL;
    //build phase s[i + 1] from s[i]
    for(int i = 0; i < len; ++i){
        //implicity do extensions to s[0, last_non]
        *e = i + 1;
        //build s[j + 1, i + 1] from s[j, i]
        //current is the last node(s[j, i] for consitency)
        //for the s[last_non + 1, i + 1], current is the s[ last_non, i]
        base = last_non;
        remain_len = i - last_non + 1;
        current = root;
        //printf("remain_len, base %d %d\n", remain_len, base);
        walk_down(&current, remain_len, base);
        if(current->leaf_index >= 0){
            remain_len = edge_len(current);
            base = current->start;
            current = current->parent;
        }
        //printf("remain_len, base %d %d\n", remain_len, base);
        //remain_len++;
        for(int j = last_non + 1; j <= i + 1; ++j){
            //printf("current->leaf_index %d\n", current->leaf_index);
            if(current == root){
                remain_len--;
                base++;
            }
            else{
                current = current->suffix_link;
            }
            //printf("origin remain_len, base %d %d\n", remain_len, base);
            walk_down(&current, remain_len, base);
            //printf("after remain_len,base %d %d\n", remain_len, base);
            if(pre != NULL){
                if(current->leaf_index >= 0){ //now at a leaf
                    pre->suffix_link = current->parent;
                }
                else{
                    pre->suffix_link = current;
                }
            }
            if(current->leaf_index >= 0){ //rule 1
                //puts("rule 1");
                remain_len = edge_len(current);
                current->end = e;
                last_non = j;
                base = current->start;
                pre = NULL;
                current->leaf_index = j;
                current = current->parent;
            }
            else{
                if(remain_len == 0){
                    if(current->child.find(str[i + 1]) == current->child.end()){
                        //puts("new leaf added in(rule 2)");
                        node* new_leaf = get_next(i + 1, e, NULL, current, j);
                        current->child[str[i + 1]] = new_leaf;
                        last_non = j;
                        remain_len = 0;
                        base = new_leaf->start;
                        pre = NULL;
                        continue;
                    }
                    else{
                        //puts("rule 3");
                        //node *next = current->child[str[i + 1]];
                        //base = next->start;
                        remain_len = 0;
                        last_non = j - 1;
                        pre = NULL;
                        break;
                    }
                }
                node *next = current->child[str[base]];
                //printf("next->leafindex %d\n", next->leaf_index);
                if( str[next->start + remain_len] == str[i + 1]){ //rule 3
                    //puts("rule 3");
                    base = next->start;
                    last_non = j - 1;
                    pre = NULL;
                    break;
                }
                else{ //rule 2
                    //puts("rule 2");
                    int* middle_end = new int(next->start + remain_len - 1);
                    //printf("middle_end, remain_len %d %d\n", *middle_end, remain_len);
                    node* middle = get_next(next->start, middle_end, NULL, current, -1);
                    current->child[str[next->start]] = middle;
                    next->start = (*middle_end) + 1;
                    middle->child[str[next->start]] = next;
                    node *new_leaf = get_next(i + 1, e, NULL, middle, j);
                    middle->child[str[i + 1]] = new_leaf;
                    if(pre != NULL){
                        pre->suffix_link = middle;
                    }
                    pre = middle;
                    current = middle->parent;
                    remain_len = edge_len(middle);
                    base = middle->start;
                    last_non = j;
                    //puts("rule 2 finished");
                }
            }
        }
    }
}

void print(node* now){
    printf("started %d\n", now->leaf_index);
    printf("%d %d\n", now->start, *now->end);
    for(std::map<char, node*>::iterator itr = now->child.begin(); itr != now->child.end(); ++itr){
        printf("%c\n", itr->first);
        print(itr->second);
    }
    printf("finished %d\n", now->leaf_index);
}


void match(){
    node* now = root;
    int matched = 0, last_part = 0;
    //try to match the pattern[i]
    //the now is the matched node of pattern[i - 1]
    //last_part is the remain part along the now node
    //matched is the current total matched length
    //if match is not possible, then now = root, last_part = 0;
    for(int i = 0; i < pattern_len; ++i){
        find_next(&now, matched, last_part, i);
        //printf("now matched last_part, %d %d %d\n", now->leaf_index, matched, last_part);
        ans = std::max(ans, matched);
    }
}

int main(){
    scanf("%s", str);
    scanf("%s", pattern);
    len = strlen(str);
    pattern_len = strlen(pattern);
    init();
    build();
    //puts("print tree-----------");
    //print(root);
    match();
    printf("%d\n", ans);
    return 0;
}
