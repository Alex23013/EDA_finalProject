#include <iostream>
#include <fstream>
#include "CsvLector.h"
#include "Classes.h"

#include <string>

using namespace std;


int main() {
    //string name = "files/YearPredictionMSD.txt";
    string name = "files/Year100.txt";
    ifstream file(name);
    auto allRegisters = readCSV(file, false);
    
    for(int i =0;i<10;i++){
        ///allRegisters[registro][columna]
        cout<<allRegisters[i][0]<<"["<<i<<"]";
    }
    //cout<<comparePoints(allRegisters[8],allRegisters[9],0);  
    
    st exValue = "3.14";
    CInternalNode node(exValue);
    cout<<"\nmedian: "<<node.median;
    
    vector<vector<st>> exVector(10);
    for(int i =0;i<10;i++){
        for(int j =0;j<10;j++){
            exVector[i].push_back(allRegisters[i][j]);
        }
     }
    CLeafBlock leafBlock(exVector);  

    CLeafNode leaf("0","10",&leafBlock);
    cout<<"\nval[0][0]: "<<leaf.myBlock->regists[0][0];
}
