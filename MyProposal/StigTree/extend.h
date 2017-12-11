#include <string> 
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using Point = vector<string>;
#define Tpair pair<int, float>

vector<int> getFirst(vector<Tpair> pairs){
  vector<int> res(0);
  for(int i = 0;i < pairs.size() ; i++){
    res.push_back(pairs[i].first);
  }
  return res;
}

inline vector<string> splitStr(const string &str, const char delim) {
  // Splits a string, using delim as the delimiter and return
  // a vector with the result.
  vector<string> res;
  size_t fnd = str.find_first_of(delim);
  size_t pos = 0;
  while (fnd != string::npos) {
    res.emplace_back(str, pos, fnd - pos);
    pos = fnd + 1;
    fnd = str.find_first_of(delim, fnd + 1);
  }
  res.emplace_back(str, pos, fnd - pos);
  return res;
}

inline vector<string> splitStr(const string &str, const char delim,
                               const size_t itemsQtty) {
  // Same as splitStr, but extract a certain number of items
  // or all the items if you know their quantity.
  // More efficient than splitStr if you know the item quantity.
  vector<string> res(itemsQtty);
  size_t fnd = str.find_first_of(delim);
  size_t pos = 0;
  size_t i = 0;
  while (fnd != string::npos and i < itemsQtty) {
    res[i] = string(str, pos, fnd - pos);
    pos = fnd + 1;
    fnd = str.find_first_of(delim, fnd + 1);
    i++;
  }
  res[i] = string(str, pos, fnd - pos);
  return res;
}

inline size_t countSplits(const string &str, const char delim) {
  // Count the items(splits) in a string.
  size_t cnt = count(str.begin(), str.end(), delim);
  if (!str.empty())
    cnt++;
  return cnt;
}

inline size_t countFileLines(istream &file) {
  size_t cnt = count(istreambuf_iterator<char>(file), {}, '\n');
  file.seekg(ios_base::beg);
  return cnt;
}

inline vector<Point> readCSV(istream &file, const bool hasHeader) {
  char delim = ',';
  string line;
  size_t numLines = countFileLines(file);
  size_t numSplits;
  size_t i;
  vector<Point> points;
  if (hasHeader) {
    getline(file, line);
    numLines--;
    numSplits = countSplits(line, delim);
    points = vector<Point>(numLines, Point());
    i = 0;
  } else {
    getline(file, line);
    Point tmp = splitStr(line, delim);
    numSplits = tmp.size();
    points = vector<Point>(numLines, Point());
    points[0] = move(tmp);
    i = 1;
  }
  for (; i < numLines; i++) {
    getline(file, line);
    points[i] = splitStr(line, delim, numSplits);
  }
  return points;
}


