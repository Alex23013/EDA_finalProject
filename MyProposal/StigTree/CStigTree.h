#include "CStigNode.h"

class CStigTree {
public: //TODO pasar los atributos a private
  CStigNode* root;
  int dimensions; 
  
  CStigTree(int iDimensions);
    
  void createIndex(CStigNode* node, int currentdim);
  
  vector<CStigNode*> searchTree(CStigNode* node, int currentDim, vector<float> key); // buscar el conjunto donde puede estar
  string searchInLeaf(int idx); // buscar el registro en una hoja
  
  void createInOrderArray(CStigNode* node, vector<int> &res);
   
  ~CStigTree(){};
};

