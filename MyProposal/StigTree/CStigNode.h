#include <vector>
using namespace std;


class CStigNode {
public: //TODO pasar los atributos a private
  int idxData;
  float BBoxMin;
  float BBoxMax;
  CStigNode* childs[2];
  vector<int> idxRecords;

  CStigNode(){
    idxData = 0;
    BBoxMin = 0.0f;
    BBoxMax = 0.0f;
    childs[0] = childs[1] = nullptr; 
    idxRecords=vector<int>(0);
  }
  
  CStigNode(const vector<int> &data){
    idxData = 0;
    BBoxMin = 0.0f;
    BBoxMax = 0.0f;
    childs[0] = childs[1] = nullptr; 
    idxRecords=data;
  }
  ~CStigNode(){};
};
