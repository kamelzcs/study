#include<string>
#include<iostream>
using namespace std;

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        for(int i = 0; i < 26; ++i){
            child[i] = NULL;
        }
        end = false;
    }
    TrieNode* insert(char c){
        int offset = c - 'a';
        if(child[offset]){
            return child[offset];
        }
        TrieNode* new_node = new TrieNode();
        child[offset] = new_node;
        return new_node;
    }
    TrieNode* next(char c){
        return child[c - 'a'];
    }
    ~TrieNode(){
        for(int i = 0; i < 26; ++i){
            delete child[i];
        }
    }
    TrieNode* child[26];
    bool end;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode *current = root;
        for(char c : word){
            current = current->insert(c);
        }
        current->end = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* current = root;
        int index = 0;
        while(index < (int)word.size()){
            current = current->next(word[index]);
            if(current == NULL){
                return false;
            }
            index++;
        }
        return current->end;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* current = root;
        int index = 0;
        while(index < (int)prefix.size()){
            current = current->next(prefix[index]);
            if(current == NULL){
                return false;
            }
            index++;
        }
        return true;
    }
    ~Trie(){
        delete root;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
int main(){
    Trie trie;
    trie.insert("aa");
    cout<<trie.search("ba");
    cout<<trie.startsWith("a");
    return 0;
}
