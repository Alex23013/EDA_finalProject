#include <utility> 
#include <fstream>

#include <algorithm> 
#include "CStigTree.h"
#include "extend.h"
#include "utils.hpp"
#include <iostream>
using namespace std;

#define BSZ 1024//100
#define Tpair pair<int, float>

CStigTree ::  CStigTree(int iDimensions){
  root = nullptr;
  dimensions = iDimensions;
  string name = "files/YearPredictionMSD.txt";
  ifstream file(name);
  allRegisters = readCSV(file, false);
  /*for(int i =0;i<10;i++){
        ///allRegisters[registro][columna]
        cout<<allRegisters[i][0]<<"["<<i<<"]";
    }*/
}

vector<Tpair> CStigTree :: load (vector<int> idxRecords, int currentdim){
  vector<Tpair> res(0);
  string::size_type sz;
  float value;
  if(currentdim == 1){
    for(int i =0;i<allRegisters.size();i++){
        value = stof(allRegisters[i][0],&sz);
        res.push_back(make_pair(i,value));
    } 
  }else{
    for(int k =0;k<idxRecords.size();k++){
      value = stof(allRegisters[idxRecords[k]][currentdim],&sz);
      res.push_back(make_pair(idxRecords[k],value));
    }
  }
  return res;
}

  
void CStigTree :: createIndex(CStigNode* node, int currentdim){
  cout<<"["<<currentdim<<"]";
  if(node->idxRecords.size() <= BSZ ){
    return;
  }
  
  vector<Tpair> toSort = load(node->idxRecords,currentdim+1);// fields start in 1
  /*cout<<"nodes To Sort: \n";
  for(int i =0;i< toSort.size();i++){
    cout<<toSort[i].second<<" ";
  }*/
  //cout<<"[tS "<<currentdim;
  sort(toSort.begin(), toSort.end(), [](auto &left, auto &right) {
    return left.second < right.second;
  });
  //cout<<" tS] ";
  /*cout<<"\nnodes Sorted: \n";
  for(int i =0;i< toSort.size();i++){
    cout<<toSort[i].first<<"-"<<toSort[i].second<<" ";
  }*/
  int posMedian = toSort.size()/2;
  //cout<< "\nposMedian "<< posMedian;
  node->BBoxMin = toSort[0].second;
  node->BBoxMax = toSort[toSort.size()-1].second;
  //cout<<"\nBBox: ["<<  node->BBoxMin<<","<<node->BBoxMax<<"]";
  
  vector<Tpair> v1(toSort.begin(),toSort.begin() + posMedian);
  vector<Tpair> v2(toSort.begin() + posMedian,toSort.end());
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
  node->childs[0] = new  CStigNode(idxleft);
  node->childs[1] = new  CStigNode(idxright);
  
  createIndex(node->childs[0],currentdim+1);
  createIndex(node->childs[1],currentdim+1);
}

void CStigTree :: createInOrderArray(CStigNode* node,vector<int>& res){
  if(!node){return;}
  createInOrderArray(node->childs[0],res);
  res.insert(res.end(), node->idxRecords.begin(), node->idxRecords.end());
  //res.push_back(node->idxData);
  createInOrderArray(node->childs[1],res);
}
