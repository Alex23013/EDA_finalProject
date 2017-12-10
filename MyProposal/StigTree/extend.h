#include <string> 
#include <iostream>
using namespace std;

#define Tpair pair<int, float>

vector<Tpair> load (vector<int> idxRecords, int currentdim){
  string name = "files/";
  name+=to_string(currentdim);
  name+=".txt";
  cout<<"FileName "<<name<<endl;
  
  ifstream file(name);
  vector<Tpair> res(0);
	string line;
  int idx;
  float value;
  string::size_type sz;
  std::vector<int>::iterator it;
  int i =0;
  while(getline(file,line)){
      //idx=stoi(line.substr(0,line.find(",")));
      if(currentdim == 1){
        value = stof(line.substr(line.find(",")+1,line.size()-1),&sz);
        res.push_back(make_pair(i,value));
      }else{
        
      it = find (idxRecords.begin(), idxRecords.end(), i);
        if(it != idxRecords.end()){
          value = stof(line.substr(line.find(",")+1,line.size()-1),&sz);
          res.push_back(make_pair(i,value));      
        }
      }
      i++;      
    }
  
  return res;
}

vector<int> getFirst(vector<Tpair> pairs){
  vector<int> res(0);
  for(int i = 0;i < pairs.size() ; i++){
    res.push_back(pairs[i].first);
  }
  return res;
}

/*
inline int byteToInt(const char* memblock) {
    int result =
        (unsigned char)(memblock[3]) |
        (unsigned char)(memblock[2]) << 8  |
        (unsigned char)(memblock[1]) << 16 |
        (unsigned char)(memblock[0]) << 24;
    return result;
}

// Lee un entero desde un archivo.
int TableManagement:: readInt(const int& start) {
    char *memblock = new char[4];
    file.seekg(start, ios::beg);
    file.read(memblock, 4);
    int result = byteToInt(memblock);
    delete[] memblock;
    return result;
}

// Lee un string desde un archivo.
string TableManagement::readString(const int& start, const int& size) {
    char *memblock = new char[size];
    file.seekg(start, ios::beg);
    file.read(memblock,size);

    string result = byteToString(memblock, size);
    delete[] memblock;
    return result;
}

*/
