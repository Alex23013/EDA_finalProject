#include <string>
#include <utility>
#include <vector>
using namespace std;

///selectedType
#define st string

using Records = vector<st>;


class CInternalNode {
public: //TODO pasar los atributos a private
  st median;
  CInternalNode *childs[2];

  CInternalNode() {
    median = 0.0f;
    childs[0] = childs[1] = nullptr;
  }

  CInternalNode(const st &data) {
    this->median = data;
    childs[0] = childs[1] = nullptr;
  }
  
  ~CInternalNode(){};
};

class CLeafBlock {
public: //TODO pasar los atributos a private
  vector<Records> regists;
  
  CLeafBlock() {
    regists=vector<Records>(0); 
    }

  CLeafBlock(const vector<Records> &data) {
    regists=data;
    }
  
  ~CLeafBlock(){};
};


class CLeafNode {
public://TODO pasar los atributos a private
  pair <st,st> bBox; ///BoundingBox
  CLeafBlock * myBlock;
  
  CLeafNode() {
    bBox = pair<st,st>(0,0);
    myBlock = nullptr;
  }

  CLeafNode(const st data1,const st data2,CLeafBlock* dataBlock ) {
    this->bBox = make_pair(data1, data2);
    myBlock = dataBlock;
  }

  ~CLeafNode(){};
};
