#include<string>
#include<iostream>
using namespace std;

int minimumExpression(string s) {

   s = s + s;

   int len = s.size(), i = 0, j = 1, k = 0;

   while(i + k < len && j + k < len) {
      if(s[i+k] == s[j+k]) k++;
      else{
          if(s[i+k] > s[j+k]) {
              i = max(j + 1, i + k + 1);
          }
          else{
              j = max(i + 1, j + k + 1);
          }
          k = 0;
      }
   }
   return min(i, j);
}

int main(){
    int t;
    cin>>t;
    while(t--){
        string temp;
        cin>>temp;
        cout<<minimumExpression(temp) + 1<<endl;
    }
    return 0;
}
