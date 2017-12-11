#include <utility> 
#include <fstream>
#include<set>
#include <algorithm> 
#include "CStigTree.h"
#include "extend.h"
#include <iostream>
using namespace std;

#define BSZ 1024
#define Tpair pair<int, float>
#define TpairStig pair<CStigNode*,int>

CStigTree ::  CStigTree(int iDimensions){
  root = nullptr;
  dimensions = iDimensions;
  string name = "files/Year.txt";
  //string name = "files/YearPredictionMSD.txt";
  ifstream file(name);
  allRegisters = readCSV(file, false);
}

vector<Tpair> CStigTree :: load (vector<int> idxRecords, int currentDim){
  vector<Tpair> res(0);
  float value;
  if(currentDim == 0){
    for(int i =0;i<allRegisters.size();i++){
        value =allRegisters[i][0];
        res.push_back(make_pair(i,value));
    } 
  }else{
    for(int k =0;k<idxRecords.size();k++){
      value = allRegisters[idxRecords[k]][currentDim];
      res.push_back(make_pair(idxRecords[k],value));
    }
  }
  return res;
}

  
void CStigTree :: createIndex(CStigNode* node, int currentDim){
  int d = currentDim%dimensions;
  vector<float> aaa;
  if(node->idxRecords.size() <= BSZ ){
      for(int i =0;i< node->idxRecords.size();i++){
          aaa.push_back(allRegisters[node->idxRecords[i]][d]);
      }
      auto result = std::minmax_element(aaa.begin(),aaa.end());
      node->BBoxMin = aaa[result.first - aaa.begin()];
      node->BBoxMax = aaa[result.second - aaa.begin()];
      return;
  }
  
  vector<Tpair> toSort = load(node->idxRecords,d);
  sort(toSort.begin(), toSort.end(), [](auto &left, auto &right) {
    return left.second < right.second;
  });
  int posMedian = toSort.size()/2;
  node->idxData = toSort[posMedian].second;
    vector<Tpair> v1(toSort.begin(),toSort.begin() + posMedian);
  vector<Tpair> v2(toSort.begin() + posMedian,toSort.end()); ////STIG/ median+1
  vector<int> idxleft = getFirst(v1);
  vector<int> idxright = getFirst(v2);
  node->idxRecords.clear();
  node->childs[0] = new  CStigNode(idxleft);
  node->childs[1] = new  CStigNode(idxright);
  
  createIndex(node->childs[0],d+1);
  createIndex(node->childs[1],d+1);
}

void CStigTree :: searchTree(CStigNode* node, int currentDim, vector<float> key, set<TpairStig>& res){
  int d = currentDim%dimensions;
  float searchedKey = key[d];
  
  if(node->idxRecords.size() != 0){
    if(node->inBox(searchedKey)){
      //cout<<" ans";
      //cout<<"["<<node->BBoxMin<<"__"<<node->BBoxMax<<"]";
      res.insert(make_pair(node,d));
    }
    return;
  }
   if (searchedKey <= node->idxData){
      searchTree(node->childs[0],d+1,key,res);
   }
   if(searchedKey >= node->idxData) {
      searchTree(node->childs[1],d+1,key,res);
   }
}

bool CStigTree :: searchInLeaf(set<TpairStig> res, vector<float> key, vector<float>& regFound){
  std::set<TpairStig>::iterator it;
  for (it=res.begin(); it!=res.end(); ++it){
    for(int j =0;j<(*it).first->idxRecords.size();j++){
        float tmp = allRegisters[(*it).first->idxRecords[j]][(*it).second];
        if(key[(*it).second] == tmp){
          regFound = allRegisters[(*it).first->idxRecords[j]]; 
          return (key == allRegisters[(*it).first->idxRecords[j]]); 
        }
    }
  }
  return false;
}

bool CStigTree :: findReg(vector<float> key){
  set<TpairStig> res1;
  std::set<TpairStig>::iterator it;
  searchTree(root, 0,key,res1);
  vector<float> finalAns;
  return searchInLeaf(res1,key,finalAns);  
}

void CStigTree :: createInOrderArray(CStigNode* node,vector<int>& res){
  if(!node){return;}
  createInOrderArray(node->childs[0],res);
  res.insert(res.end(), node->idxRecords.begin(), node->idxRecords.end());
  createInOrderArray(node->childs[1],res);
}
