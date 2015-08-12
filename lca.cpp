#include<map>
#include<math.h>
#include<iostream>
#include<memory.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    map<TreeNode*, int> node_index;
    int cur_node_index;
    int max_depth;
    int root_index;
    int N;
    int T[10010], L[10010], P[10010][20];
    void mapNodeToIndex(TreeNode* root){
      if(node_index.find(root) == node_index.end()){
        node_index[root] = cur_node_index++;
      }
      if(root->left){
        mapNodeToIndex(root->left);
      }
      if(root->right){
        mapNodeToIndex(root->right);
      }
    }
    void calDepth(TreeNode* root, int cur_depth){
      int root_index = node_index[root];
      L[root_index] = cur_depth;
      max_depth= max(max_depth, cur_depth);
      if(root->left){
        T[node_index[root->left]] = root_index;
        calDepth(root->left, cur_depth + 1);
      }
      if(root->right){
        T[node_index[root->right]] = root_index;
        calDepth(root->right, cur_depth + 1);
      }
    }
    void calP(){
      memset(P, 0xff, sizeof(P));
      T[root_index] = root_index;
      for(int i = 0; i < N; ++i){
        P[i][0] = T[i];
      }
      for(int j = 0; (1<<j) < N; ++j){
        for(int i = 0; i < N; ++i){
          if(P[i][j - 1] != -1){
            P[i][j] = P[P[i][j - 1]][j - 1];
          }
        }
      }
    }

    int lca(int x, int y){
      if(L[x] < L[y]){
        swap(x, y);
      }
      int log;
      for(log = 1; (1<<log) <= L[x]; ++log);
      log--;
      int delta = L[x] - L[y];
      for(int i = 0; (1<<i) <= delta; ++i){
        if((1<<i) & delta){
          x = P[x][i];
        }
      }
      if(x == y){
        return x;
      }
      for(int i = log; i >= 0; --i){
        if(P[x][i] != -1 && P[x][i] != P[y][i]){
          x = P[x][i];
          y = P[y][i];
        }
      }
      return T[x];
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
      cur_node_index = 0;
      node_index.clear();
      mapNodeToIndex(root);
      N = cur_node_index;
      calDepth(root, 0);
      root_index = node_index[root];
      calP();
      int ans_index = lca(node_index[p], node_index[q]);
      for(auto const &it1 : node_index) {
        if(it1.second == ans_index){
          return it1.first;
        }
      }
    }
};
