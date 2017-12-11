#include <iostream>
#include <vector>
#include <set>
#include "CStigTree.h"

using namespace std;

int main() {

cout<<"------------- STIG TREE -------------\n";
CStigTree treeEx(9);
cout<< "tree created with "<< treeEx.dimensions <<" dim\n";

vector<int> vectorEx(515345,0);
CStigNode nodeEx(vectorEx);

treeEx.root = &nodeEx;
treeEx.createIndex(treeEx.root, 0); 
vector<int> res(0);
treeEx.createInOrderArray(treeEx.root,res);
cout<<"\nlinear vector of idx\n";
cout<<"size: "<<res.size()<<endl;
for(int i =0;i< res.size();i++){
  cout<<res[i]<<" ";
}
cout<<endl;

vector<float> key = {2001,49.75468,33.99581,56.73846,2.89581};
treeEx.findReg(key);

return 0;
}
