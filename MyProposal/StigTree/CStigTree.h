#include "CStigNode.h"
#include <set>


using Point = vector<float>;
#define Tpair pair<int, float>
#define TpairStig pair<CStigNode*,int>
class CStigTree {
public: 
  CStigNode* root;
  int dimensions; 
  vector<Point> allRegisters;
  
  CStigTree(int iDimensions);
  vector<Tpair> load (vector<int> idxRecords, int currentdim);  
  void createIndex(CStigNode* node, int currentdim);
  
  void searchTree(CStigNode* node, int currentDim,
     vector<float> key,set<TpairStig>& res);
  bool searchInLeaf(set<TpairStig> res,
   vector<float> key, vector<float>& regFound);
  
  bool findReg(vector<float> key);
  
  void createInOrderArray(CStigNode* node, vector<int> &res);
  
  vector<float> searchTreeP(vector<int> toSearch,vector<float> key, int total);
  void thr_searchP(vector<int> toSearch, const size_t start, const size_t end,
       vector<float> key, vector<bool>& res);
   
  ~CStigTree(){};
};

