/*
 * clonegraph.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<algorithm>
#include<unordered_map>
using namespace std;
struct UndirectedGraphNode {
 int label;
 vector<UndirectedGraphNode *> neighbors;
 UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
    unordered_map<int, UndirectedGraphNode*> nodeHash;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node==NULL) return NULL;
        int label=node->label;
        unordered_map<int, UndirectedGraphNode*>::iterator itr = nodeHash.find(label);
        if(itr == nodeHash.end()){
            UndirectedGraphNode *newNode = new UndirectedGraphNode(label);
            nodeHash[label] = newNode;
            for(vector<UndirectedGraphNode *>::iterator itr= node->neighbors.begin(); itr!= node->neighbors.end(); ++itr){
                newNode->neighbors.push_back(cloneGraph(*itr));
            }
            return newNode;
        }
        else return itr->second;
    }
};
