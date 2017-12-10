#include "CStigNode.h"
using Point = vector<string>;
#define Tpair pair<int, float>
class CStigTree {
public: //TODO pasar los atributos a private
  CStigNode* root;
  int dimensions; 
  vector<Point> allRegisters;
  
  CStigTree(int iDimensions);
  vector<Tpair> load (vector<int> idxRecords, int currentdim);  
  void createIndex(CStigNode* node, int currentdim);
  
  vector<CStigNode*> searchTree(CStigNode* node, int currentDim, vector<float> key); // buscar el conjunto donde puede estar
  string searchInLeaf(int idx); // buscar el registro en una hoja
  
  void createInOrderArray(CStigNode* node, vector<int> &res);
   
  ~CStigTree(){};
};

