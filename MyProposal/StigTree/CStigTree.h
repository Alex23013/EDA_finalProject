#include "CStigNode.h"
#include <set>
using Point = vector<string>;
#define Tpair pair<int, float>
#define TpairStig pair<CStigNode*,int>

class CStigTree {
public: //TODO pasar los atributos a private
  CStigNode* root;
  int dimensions; 
  vector<Point> allRegisters;
  
  CStigTree(int iDimensions);
  vector<Tpair> load (vector<int> idxRecords, int currentdim);  
  void createIndex(CStigNode* node, int currentdim);
  
  void searchTree(CStigNode* node, int currentDim, vector<float> key,set<TpairStig>& res);
  bool searchInLeaf(set<TpairStig> res, vector<float> key, vector<string>& regFound);
  
  bool findReg(vector<float> key);
  
  void createInOrderArray(CStigNode* node, vector<int> &res);
   
  ~CStigTree(){};
};

