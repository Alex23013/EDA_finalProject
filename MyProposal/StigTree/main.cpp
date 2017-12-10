#include <iostream>
#include <vector>
#include "CStigTree.h"

using namespace std;


int main() {

cout<<"------------- STIG TREE -------------\n";
CStigTree treeEx(9);
cout<< "tree created with "<< treeEx.dimensions <<" dim\n";

vector<int> vectorEx(515345,3);
CStigNode nodeEx(vectorEx);
/*for(int i =0;i< nodeEx.idxRecords.size();i++){
  cout<<nodeEx.idxRecords[i]<<" ";
}
*/
treeEx.root = &nodeEx;
cout<<"dataRoot "<<treeEx.root->idxData<<endl;
treeEx.createIndex(treeEx.root, 0); 
vector<int> res(0);
treeEx.createInOrderArray(treeEx.root,res);
cout<<"\nlinear vector of idx\n";
cout<<"size: "<<res.size();
/*for(int i =0;i< res.size();i++){
  cout<<res[i]<<" ";
}*/

return 0;
}
