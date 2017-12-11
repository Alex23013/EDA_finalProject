#include <iostream>
#include <vector>
#include <set>
#include "CStigTree.h"

using namespace std;

int main() {

cout<<"------------- STIG TREE -------------\n";
CStigTree treeEx(90);
cout<< "tree created with "<< treeEx.dimensions <<" dim\n";
vector<int> vectorEx(515345,0);

CStigNode nodeEx(vectorEx);

treeEx.root = &nodeEx;
int numTest = 10;
double xCreate;
//for(int i =0 ;i< numTest;i++){
  clock_t startCreate = clock();
  treeEx.createIndex(treeEx.root, 0);
  xCreate += (clock() - startCreate) / (double)(CLOCKS_PER_SEC);
//  treeEx.root = nullptr;
//}

//double prom = xCreate/numTest;

vector<int> res(0);
treeEx.createInOrderArray(treeEx.root,res);
cout<<"\nlinear vector of idx";
cout<<"size: "<<res.size()<<endl;
/*
for(int i =0;i< res.size();i++){
  cout<<res[i]<<" ";
}
cout<<endl;*/

vector<float> key ={2001,50.57546,33.17843,50.53517,11.55217,-27.24764,-8.78206,-12.04282,-9.53930,28.61811,8.25435,-0.43743,5.66265,11.07787,1080.98902,1230.78393,1301.63542,952.84686,783.02498,560.79536,696.19620,253.36266,316.92697,151.75689,144.07059,-3.02894,-111.65251,-56.64580,464.86598,150.52166,84.69609,-91.71196,89.31272,16.49867,-4.47074,-2.02539,13.27637,-153.73456,199.01552,-278.79072,49.72018,-226.95102,0.29774,-89.70185,6.34632,-10.95621,-27.32970,14.37464,245.76022,-29.78693,-291.28893,0.05909,-92.07551,7.80480,-46.15966,-39.03309,32.52065,164.15989,-247.22025,-100.28773,-55.58712,8.38343,-4.57294,-20.08525,-357.00069,-232.78978,-112.81679,-66.16128,43.25003,18.48417,-2.50274,3.25927,94.57509,-24.31254,62.97582,-19.41809,10.35282,-91.89392,10.51922,-74.98521,12.29948,11.63681,25.44182,134.62382,21.51982,8.17570,35.46251,11.57736,4.50056,-4.62739,1.40192};

double xFind;
clock_t start = clock();
if( treeEx.findReg(key))
  cout<<"Found!\n";
else
  cout<<"don be =(\n";
xFind = (clock() - start) / (double)(CLOCKS_PER_SEC);

/*
//PARALELO
double xFindP;
clock_t startP = clock();
if( treeEx.findRegP(key))
  cout<<"Found!\n";
else
  cout<<"don be =(\n";
xFindP = (clock() - start) / (double)(CLOCKS_PER_SEC);

*/
cout<<endl<<"Tiempo:\n busqueda: "<<xFind;//<<" \t P "<<xFindP<<"\n create: "<<xCreate<<endl;
cout<<"\n create: "<<xCreate<<endl;
return 0;
}
