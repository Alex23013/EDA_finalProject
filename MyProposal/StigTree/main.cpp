#include <iostream>
#include <vector>
#include <set>
#include "CStigTree.h"

#include <chrono>
#include <utility>
#include <algorithm>
using namespace std;
using namespace std::chrono;

void menu()
{

    cout<<"1) print linear tree"<<endl;
    cout<<"2) busqueda"<<endl;
    cout<<"3) tomar tiempos"<<endl;
    cout<<"6) Salir"<<endl;
    cout<<"Opcion -> ";
}



int main() {

cout<<"------------- STIG TREE -------------\n";
CStigTree treeEx(90);
cout<< "tree created with "<< treeEx.dimensions <<" dim\n";
vector<int> vectorEx(515345,0);

CStigNode nodeEx(vectorEx);

treeEx.root = &nodeEx;
double xCreate;
clock_t startCreate = clock();
treeEx.createIndex(treeEx.root, 0);
xCreate += (clock() - startCreate) / (double)(CLOCKS_PER_SEC);
cout<<"\n tiempo create index: "<<xCreate*1000<<" ms"<<endl;
menu();
int option;
    cin>>option;
    while (option<6){
        switch(option){
            case 1: //printLinearTree
            {
              vector<int> res(0);
              treeEx.createInOrderArray(treeEx.root,res);
              cout<<"\nlinear vector of idx";
              cout<<"size: "<<res.size()<<endl;
              /*
              for(int i =0;i< res.size();i++){
                cout<<res[i]<<" ";
              }
               cout<<endl;*/          
            break;}
            case 2: //busqueda
            {
              vector<float> key ={2001,50.57546,33.17843,50.53517,11.55217,-27.24764,-8.78206,-12.04282,-9.53930,28.61811,8.25435,-0.43743,5.66265,11.07787,1080.98902,1230.78393,1301.63542,952.84686,783.02498,560.79536,696.19620,253.36266,316.92697,151.75689,144.07059,-3.02894,-111.65251,-56.64580,464.86598,150.52166,84.69609,-91.71196,89.31272,16.49867,-4.47074,-2.02539,13.27637,-153.73456,199.01552,-278.79072,49.72018,-226.95102,0.29774,-89.70185,6.34632,-10.95621,-27.32970,14.37464,245.76022,-29.78693,-291.28893,0.05909,-92.07551,7.80480,-46.15966,-39.03309,32.52065,164.15989,-247.22025,-100.28773,-55.58712,8.38343,-4.57294,-20.08525,-357.00069,-232.78978,-112.81679,-66.16128,43.25003,18.48417,-2.50274,3.25927,94.57509,-24.31254,62.97582,-19.41809,10.35282,-91.89392,10.51922,-74.98521,12.29948,11.63681,25.44182,134.62382,21.51982,8.17570,35.46251,11.57736,4.50056,-4.62739,1.40192};

              double xFind;
              clock_t start = clock();
              cout<<"First search\n";
              if( treeEx.findReg(key))
                cout<<"Found!\n";
              else
                cout<<"don be =(\n";
              xFind = (clock() - start) / (double)(CLOCKS_PER_SEC);
              
              
              vector<float> key1 ={2031,50.57546,33.17843,50.53517,11.55217,-27.24764,-8.78206,-12.04282,-9.53930,28.61811,8.25435,-0.43743,5.66265,11.07787,1080.98902,1230.78393,1301.63542,952.84686,783.02498,560.79536,696.19620,253.36266,316.92697,151.75689,144.07059,-3.02894,-111.65251,-56.64580,464.86598,150.52166,84.69609,-91.71196,89.31272,16.49867,-4.47074,-2.02539,13.27637,-153.73456,199.01552,-278.79072,49.72018,-226.95102,0.29774,-89.70185,6.34632,-10.95621,-27.32970,14.37464,245.76022,-29.78693,-291.28893,0.05909,-92.07551,7.80480,-46.15966,-39.03309,32.52065,164.15989,-247.22025,-100.28773,-55.58712,8.38343,-4.57294,-20.08525,-357.00069,-232.78978,-112.81679,-66.16128,43.25003,18.48417,-2.50274,3.25927,94.57509,-24.31254,62.97582,-19.41809,10.35282,-91.89392,10.51922,-74.98521,12.29948,11.63681,25.44182,134.62382,21.51982,8.17570,35.46251,11.57736,4.50056,-4.62739,1.40192};

              double xFind1;
              clock_t start1 = clock();
              cout<<"Second search\n";
              if( treeEx.findReg(key1))
                cout<<"Found!\n";
              else
                cout<<"don be =(\n";
              xFind1 = (clock() - start1) / (double)(CLOCKS_PER_SEC);
                            
              cout<<endl<<"Tiempo busqueda: \n1)"<<xFind*1000<<" ms \t 2)"<<xFind1*1000<<" ms\n";


            break;}
            case 3: //tiempos
            {
               // int elementos[4] = {1000,3000,5000,7000};
                int tests = 10;
                srand(time(NULL));
                //for(int i = 0; i < 4; i++){
                    //int n = elementos[i];
                    double time = 0;
                    for (int i = 0; i < tests ; i++) {

		                high_resolution_clock::time_point t1 = high_resolution_clock::now();
				                ///
				                //for(int j =0;j <n;j++){
				                  int key = rand()%10;
				                  treeEx.findReg(treeEx.allRegisters[key]);
				                //}
				                ///

		                high_resolution_clock::time_point t2 = high_resolution_clock::now();
		                auto res = duration_cast<microseconds>( t2 - t1 ).count();
                        time += res;
                    }

                    long long  ttime = time/tests;
                    cout << "tiempo:" << ttime/1000.0<< " milliseconds "<<endl ;          
                //}
            break;}
            default:
				break;
        }
        menu();
        cin>>option;
    }
return 0;
}
