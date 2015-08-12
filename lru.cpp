/*
 * lru.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<list>
#include<algorithm>
#include<unordered_map>
using namespace std;
class LRUCache{
public:
    LRUCache(int capacity):left(capacity) {
        dict.clear();
        lru.clear();
    }

    int get(int key) {
        auto it = dict.find(key);
        if(it == dict.end()) return -1;
        update(it);
        return it->second.first;
    }

    void set(int key, int value) {
        auto it = dict.find(key);
        if(it != dict.end()){
            update(it);
        }
        else{
            if(left == dict.size()){
                dict.erase(lru.back());
                lru.pop_back();
            }
            lru.push_front(key);
        }
        dict[key] = {value, lru.begin()};
    }

private:
    typedef list<int> LI;
    typedef pair<int, LI::iterator> PIL;
    typedef unordered_map<int, PIL> HPIL;
    HPIL dict;
    LI lru;
    int left;
    void update(HPIL::iterator it){
        int key = it->first;
        lru.erase(it->second.second);
        lru.push_front(key);
        it->second.second = lru.begin();
    }
};
