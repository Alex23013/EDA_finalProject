#include <utility> 
#include <fstream>
#include<set>
#include <algorithm> 
#include "CStigTree.h"
#include "extend.h"
#include "utils.hpp"
#include <iostream>
using namespace std;

#define BSZ 1024//2//100
#define Tpair pair<int, float>
#define TpairStig pair<CStigNode*,int>

CStigTree ::  CStigTree(int iDimensions){
  root = nullptr;
  dimensions = iDimensions;
  //string name = "files/10regs/Year.txt";
  string name = "files/YearPredictionMSD.txt";
  ifstream file(name);
  allRegisters = readCSV(file, false);
  /*for(int i =0;i<10;i++){
        ///allRegisters[registro][columna]
        cout<<allRegisters[i][0]<<"["<<i<<"]";
    }*/
}

vector<Tpair> CStigTree :: load (vector<int> idxRecords, int currentDim){
  vector<Tpair> res(0);
  string::size_type sz;
  float value;
  if(currentDim == 0){
    for(int i =0;i<allRegisters.size();i++){
        value = stof(allRegisters[i][0],&sz);
        res.push_back(make_pair(i,value));
    } 
  }else{
    for(int k =0;k<idxRecords.size();k++){
      value = stof(allRegisters[idxRecords[k]][currentDim],&sz);
      res.push_back(make_pair(idxRecords[k],value));
    }
  }
  return res;
}

  
void CStigTree :: createIndex(CStigNode* node, int currentDim){
  int d = currentDim%dimensions;
  ///cout<<"\n["<<d;
  
  string::size_type sz;
  vector<float> aaa;
  if(node->idxRecords.size() <= BSZ ){
      for(int i =0;i< node->idxRecords.size();i++){
          aaa.push_back(stof(allRegisters[node->idxRecords[i]][d],&sz));
      }
      auto result = std::minmax_element(aaa.begin(),aaa.end());
      node->BBoxMin = aaa[result.first - aaa.begin()];
      node->BBoxMax = aaa[result.second - aaa.begin()];
      ///cout<<"\nBBox: ["<<  node->BBoxMin<<","<<node->BBoxMax<<"]"; 
    ///cout<<"r]";
    return;
  }
  ///cout<<"]";
  
  vector<Tpair> toSort = load(node->idxRecords,d);
  /*cout<<"nodes To Sort: \n";
  for(int i =0;i< toSort.size();i++){
    cout<<toSort[i].second<<" ";
  }*/
  //cout<<"[tS "<<d;
  sort(toSort.begin(), toSort.end(), [](auto &left, auto &right) {
    return left.second < right.second;
  });
  //cout<<" tS] ";
 /* cout<<"\nnodes Sorted: \n";
  for(int i =0;i< toSort.size();i++){
    cout<<toSort[i].first<<"-"<<toSort[i].second<<" ";
  }*/
  int posMedian = toSort.size()/2;
  ///cout<< "\nposMedian ";//<<toSort[posMedian].first <<" "<<
  ///cout<<toSort[posMedian].second;
  node->idxData = toSort[posMedian].second;
  
  vector<Tpair> v1(toSort.begin(),toSort.begin() + posMedian);
  vector<Tpair> v2(toSort.begin() + posMedian,toSort.end()); ////STIG/ median+1
  vector<int> idxleft = getFirst(v1);
  vector<int> idxright = getFirst(v2);
  /*cout<<"\nidxLeft: ";
  for(int i =0;i< idxleft.size();i++){
    cout<<idxleft[i]<<" ";
  }
  cout<<"\nidxright: ";
  for(int i =0;i< idxright.size();i++){
    cout<<idxright[i]<<" ";
  }*/
  node->idxRecords.clear();
  //cout<<"idx? "<<node->idxRecords.size()<<endl;
  node->childs[0] = new  CStigNode(idxleft);
  node->childs[1] = new  CStigNode(idxright);
  
  createIndex(node->childs[0],d+1);
  createIndex(node->childs[1],d+1);
}

void CStigTree :: searchTree(CStigNode* node, int currentDim, vector<float> key, set<TpairStig>& res){
  int d = currentDim%dimensions;
  float searchedKey = key[d];
  //cout<<"searchedKey "<<searchedKey<<endl;
  if(node->idxRecords.size() != 0){
    //  cout<<"stop? ";  
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

bool CStigTree :: searchInLeaf(set<TpairStig> res, vector<float> key, vector<string>& regFound){
  std::set<TpairStig>::iterator it;
  string::size_type sz;
  for (it=res.begin(); it!=res.end(); ++it){
    for(int j =0;j<(*it).first->idxRecords.size();j++){
        float tmp = stof(allRegisters[(*it).first->idxRecords[j]][(*it).second],&sz);
        if(key[(*it).second] == tmp){
          regFound = allRegisters[(*it).first->idxRecords[j]]; 
          return true; 
        }
    }
  }
  return false;
}

bool CStigTree :: findReg(vector<float> key){
  set<TpairStig> res1;
  std::set<TpairStig>::iterator it;
  searchTree(root, 0,key,res1);
  /*cout<<"posibles leaf ";
  for (it=res1.begin(); it!=res1.end(); ++it){
    for(int j =0;j<(*it).first->idxRecords.size();j++){
      cout<<(*it).first->idxRecords[j]<<"("<<(*it).second<<") ";
      }
    cout<<"\n";
  }*/

  vector<string> finalAns;
  bool is =  searchInLeaf(res1,key,finalAns);
    /*for(int i =0;i< finalAns.size();i++){
    cout<<finalAns[i]<<" ";
    }*/
  return is;  
}

void CStigTree :: createInOrderArray(CStigNode* node,vector<int>& res){
  if(!node){return;}
  createInOrderArray(node->childs[0],res);
   res.insert(res.end(), node->idxRecords.begin(), node->idxRecords.end());
 //STIG/ if(node->idxData.first != -1)
 //STIG/   res.push_back(node->idxData.first);
 
  createInOrderArray(node->childs[1],res);
}
