#include <iostream>
#include <fstream>
#include "kdTree.hpp"
#include "tools.hpp"
#include <string>

using namespace std;


int main() {
    //string name = "dataM.csv";
    string name = "Year100.txt";
    ifstream file(name);
    auto points = readCSV(file, true);
    auto sp = points[22];
    KDTree tree(points, 100);//0000000);
    //tree.print();

    auto fnd = tree.find(sp);
    cout << (fnd != nullptr ? "Found!" : "Not Found") << endl;
}
