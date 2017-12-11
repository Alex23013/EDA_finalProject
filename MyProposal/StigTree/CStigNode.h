#include <vector>
#include<iostream>
using namespace std;

#define Tpair pair<int, float>

class CStigNode {
public: //TODO pasar los atributos a private
  float idxData;
  float BBoxMin;
  float BBoxMax;
  CStigNode* childs[2];
  vector<int> idxRecords;

  CStigNode(){
    idxData = 0.0f;
    BBoxMin = 0.0f;
    BBoxMax = 0.0f;
    childs[0] = childs[1] = nullptr; 
    idxRecords=vector<int>(0);
  }
  
  CStigNode(const vector<int> &data){
    idxData = 0.0f;
    BBoxMin = 0.0f;
    BBoxMax = 0.0f;
    childs[0] = childs[1] = nullptr; 
    idxRecords=data;
  }
  
  bool inBox(float key){
    //cout<<"["<<BBoxMin<<"__"<<BBoxMax<<"]";
    return (key>= BBoxMin) && (key <= BBoxMax); 
  }
  ~CStigNode(){};
};
