#include <utility> 
#include <fstream>
#include<set>
#include <algorithm> 
#include<thread>
#include "CStigTree.h"
#include "extend.h"
#include <iostream>
using namespace std;

#define BSZ 1024
#define Tpair pair<int, float>
#define TpairStig pair<CStigNode*,int>

CStigTree ::  CStigTree(int iDimensions){
  root = nullptr;
  dimensions = iDimensions;
  string name = "files/Year100000.txt";
  //string name = "files/YearPredictionMSD.txt"; // subset 0.5 Millon
  ifstream file(name);
  allRegisters = readCSV(file, false);
}

/*Carga una lista de pair<indice,dato> en la dimension requerida*/
vector<Tpair> CStigTree :: load (vector<int> idxRecords, int currentDim){
  vector<Tpair> res(0);
  float value;
  if(currentDim == 0){
    for(int i =0;i<allRegisters.size();i++){
        value =allRegisters[i][0];
        res.push_back(make_pair(i,value));
    } 
  }else{
    for(int k =0;k<idxRecords.size();k++){
      value = allRegisters[idxRecords[k]][currentDim];
      res.push_back(make_pair(idxRecords[k],value));
    }
  }
  return res;
}

  
void CStigTree :: createIndex(CStigNode* node, int currentDim){
  int d = currentDim%dimensions; // para no salir de las dimensiones 
  vector<float> aaa;
  if(node->idxRecords.size() <= BSZ ){ 
  // si ya llegamos a la cantidad min por nodo hoja
      for(int i =0;i< node->idxRecords.size();i++){
          aaa.push_back(allRegisters[node->idxRecords[i]][d]);
      }
      //calculando el Bounding Box en la currentDimension
      auto result = std::minmax_element(aaa.begin(),aaa.end());
      node->BBoxMin = aaa[result.first - aaa.begin()];
      node->BBoxMax = aaa[result.second - aaa.begin()];
      return;
  }
  
  vector<Tpair> toSort = load(node->idxRecords,d);
  //sort en la currentDimension
  sort(toSort.begin(), toSort.end(), [](auto &left, auto &right) {
    return left.second < right.second;
  });
  int posMedian = toSort.size()/2;
  //set el punto mediano o eje de corte en la currentDimension
  node->idxData = toSort[posMedian].second;
  // asignando las dos mitades a los hijos del nodo actual
  vector<Tpair> v1(toSort.begin(),toSort.begin() + posMedian);
  vector<Tpair> v2(toSort.begin() + posMedian,toSort.end()); 
  //asignando solo los indices
  vector<int> idxleft = getFirst(v1);
  vector<int> idxright = getFirst(v2);
  node->idxRecords.clear();
  node->childs[0] = new  CStigNode(idxleft);
  node->childs[1] = new  CStigNode(idxright);
  
  createIndex(node->childs[0],d+1);
  createIndex(node->childs[1],d+1);
}

void CStigTree :: searchTree(CStigNode* node, int currentDim, vector<float> key, set<TpairStig>& res){
  int d = currentDim%dimensions;
  float searchedKey = key[d];
  // si idxRecords.size() != 0 quiere decir que es un nodo hoja 
  //por lo tanto  hay que buscar en el Bounding Box
  if(node->idxRecords.size() != 0){
    if(node->inBox(searchedKey)){
      //Y si el valor buscado en la currentDim esta dentro del Bounding Box
      //lo ingresamos al conjunto de posibles hojas  donde esta
      res.insert(make_pair(node,d));
    }
    return;
  }
    // si no es nodo hoja
   if (searchedKey <= node->idxData){
      // si es <= que el eje de corte se busca en el child left
      searchTree(node->childs[0],d+1,key,res);
   }
   if(searchedKey >= node->idxData) {
      // si es >= que el eje de corte se busca en el child right
      searchTree(node->childs[1],d+1,key,res);
   }
}


//Buscar en todo los registros que contiene los nodos hoja encontrados en SearchTree
bool CStigTree :: searchInLeaf(set<TpairStig> res, vector<float> key, vector<float>& regFound){
  std::set<TpairStig>::iterator it;
  for (it=res.begin(); it!=res.end(); ++it){
    for(int j =0;j<(*it).first->idxRecords.size();j++){
        float tmp = allRegisters[(*it).first->idxRecords[j]][(*it).second];
        if(key[(*it).second] == tmp){
          regFound = allRegisters[(*it).first->idxRecords[j]]; 
          return (key == allRegisters[(*it).first->idxRecords[j]]); 
        }
    }
  }
  return false;
}

//Encontrar un dato
bool CStigTree :: findReg(vector<float> key){
  set<TpairStig> res1;
  std::set<TpairStig>::iterator it;
  searchTree(root, 0,key,res1);
  vector<float> finalAns;
  return searchInLeaf(res1,key,finalAns);  
}

//recorrido en inorden para las busquedas paralelas
void CStigTree :: createInOrderArray(CStigNode* node,vector<int>& res){
  if(!node){return;}
  createInOrderArray(node->childs[0],res);
  res.insert(res.end(), node->idxRecords.begin(), node->idxRecords.end());
  createInOrderArray(node->childs[1],res);
}

/*
//Busqueda Paralela
vector<float> CStigTree :: searchTreeP(vector<int> toSearch,vector<float> key, int total){
  size_t numberThreads = std::thread::hardware_concurrency();
  size_t idxByThread =
      total / numberThreads + (total % numberThreads ? 1 : 0);
  std::vector<std::thread> thds;
  vector<vector<bool>> ress(numberThreads);
  for (size_t i = 0; i < numberThreads; i++) {
    vector<bool> tm(idxByThread,false);
    thds.emplace_back(CStigTree :: thr_searchP, this,
                         toSearch,(i*idxByThread),((i+1)*idxByThread)-1,
                         key,tm);
    ress[i]=tm;                
  }

  for (auto &thread : thds)
    thread.join();
    
  
  int pos_found =0; //TODO: ver la posicion del true
  return  allRegisters[pos_found];
}


/*GPU search inOrderArray*/
/*void CStigTree :: thr_searchP(vector<int> toSearch, const size_t start, const size_t end, vector<float> key, vector<bool>& res){
 vector<float> tmp;
 for (size_t i = start; i < end; i++) {
      if(key == allRegisters[toSearch[i]] )
        {res[i]=true;}
      else
        {res[i]=false;}
 }
}
*/
