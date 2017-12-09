#include "Classes.h"

class CkdTreeSeq{
public: //TODO pasar los atributos a private
  CInternalNode *mRoot;
  int mDimensions;

  CkdTreeSeq(int dimensions);
  
  void createIndex();
  void searchLeaf();
  void searchTree();
  void findLeafBlocks();
  void print();

  ~CkdTreeSeq(){};
};
