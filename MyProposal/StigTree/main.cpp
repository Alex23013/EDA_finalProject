#include <iostream>
#include <vector>
#include "CStigTree.h"

using namespace std;


int main() {

cout<<"------------- STIG TREE -------------\n";
CStigTree treeEx(3);
cout<< "tree created with "<< treeEx.dimensions <<" dim\n";

vector<int> vectorEx(3,3);
CStigNode nodeEx(vectorEx);
for(int i =0;i< nodeEx.idxRecords.size();i++){
  cout<<nodeEx.idxRecords[i]<<" ";
}

treeEx.root = &nodeEx;
cout<<"dataRoot "<<treeEx.root->idxData<<endl;
treeEx.createIndex(treeEx.root, 0);

//TODO: pasar FULL.txt to 1,2,...15.txt
return 0;
}
