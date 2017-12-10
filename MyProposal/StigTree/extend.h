#include <string> 
#include<sstream>
#include <iostream>
using namespace std;

#define Tpair pair<int, float>

vector<int> getFirst(vector<Tpair> pairs){
  vector<int> res(0);
  for(int i = 0;i < pairs.size() ; i++){
    res.push_back(pairs[i].first);
  }
  return res;
}

