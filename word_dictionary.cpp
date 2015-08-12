#include<iostream>
using namespace std;

class Node{
    public:
    Node(){
        end = false;
        for(int i = 0; i < 26; ++i){
            child[i] = NULL;
        }
    }
    void insert(string str){
        if(str.empty()){
            end = true;
            return;
        }
        int start = str[0] - 'a';
        if(!child[start]){
            child[start] = new Node();
        }
        child[start]->insert(str.substr(1));
    }
    bool search(string str){
        if(str.empty()){
            return end;
        }
        char start = str[0];
        if(start != '.'){
            int index = start - 'a';
            if(!child[index]){
                return false;
            }
            return child[index]->search(str.substr(1));
        }
        else{
            for(int i = 0; i < 26; ++i){
                if(child[i]){
                    if(child[i]->search(str.substr(1))){
                        return true;
                    }
                }
            }
            return false;
        }
    }
    ~Node(){
        for(int i = 0; i < 26; ++i){
            delete child[i];
        }
    }
    private:
        bool end;
        Node *child[26];
};

class WordDictionary {
public:
    WordDictionary(){
        root = new Node();
    }
    ~WordDictionary(){
        delete root;
    }
    // Adds a word into the data structure.
    void addWord(string word) {
        root->insert(word);
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return root->search(word);
    }
private:
    Node *root;
};

int main(){
    WordDictionary wordDictionary;
    wordDictionary.addWord("word");
    cout<<wordDictionary.search("wo.d");
    cout<<wordDictionary.search("wo.");
    return 0;
}
// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");


