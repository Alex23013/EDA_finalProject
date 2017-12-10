#include <string> 
#include <iostream>
using namespace std;

#define Tpair pair<int, float>

vector<Tpair> load (vector<int> idxRecords, int currentdim){
  string name = "files/";
  name+=to_string(currentdim);
  name+=".txt";
  cout<<"FileName "<<name<<endl;
  
  ifstream file(name);
  //TODO: make pair del txt
  
  vector<Tpair> res(0);
  if(currentdim == 1){
    res.push_back(make_pair(0,3.14));
    res.push_back(make_pair(1,6.25));
    res.push_back(make_pair(2,0.24));
    res.push_back(make_pair(3,63.25));
    res.push_back(make_pair(4,0.0024));
  }else{
    for(int i = 0;i<  idxRecords.size();i++ ){
      res.push_back(make_pair(idxRecords[i],0.011));
    }  
  }
  
  return res;
}

vector<int> getFirst(vector<Tpair> pairs){
  vector<int> res(0);
  for(int i = 0;i < pairs.size() ; i++){
    res.push_back(pairs[i].first);
  }
  return res;
}
