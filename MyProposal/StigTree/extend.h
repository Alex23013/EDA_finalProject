#include <string> 
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using Point = vector<float>;

#define Tpair pair<int, float>

vector<int> getFirst(vector<Tpair> pairs){
  vector<int> res(0);
  for(int i = 0;i < pairs.size() ; i++){
    res.push_back(pairs[i].first);
  }
  return res;
}

inline size_t countSplits(const std::string &str, const char delim) {
  // Count the items(splits) in a string.
  size_t cnt = std::count(str.begin(), str.end(), delim);
  if (!str.empty())
    cnt++;
  return cnt;
}

inline size_t countFileLines(std::istream &file) {
  size_t cnt = count(std::istreambuf_iterator<char>(file), {}, '\n');
  file.seekg(std::ios_base::beg);
  return cnt;
}

inline Point lineToPoint(const std::string &str, const char delim,
                         const size_t numSplits) {
  Point ret(numSplits);
  size_t nextPos = std::string::npos;

  size_t i = 0;
  do {
    size_t tmp;
    ret[i] = stof(str.substr(nextPos + 1), &tmp);
    nextPos += tmp;
    nextPos = str.find_first_of(delim, nextPos);
    i++;
  } while (i < numSplits and nextPos != std::string::npos);

  return ret;
}

/*funcion extraida de la estructura con la que se comparó*/
inline std::vector<Point> readCSV(std::istream &file,
                                  const bool hasHeader = false) {
  char delim = ',';
  std::string line;
  size_t numLines = countFileLines(file);

  getline(file, line);
  size_t numSplits = countSplits(line, delim);

  if (hasHeader)
    numLines--;
  else
    file.seekg(std::ios_base::beg);

  std::vector<Point> points = std::vector<Point>(numLines, Point());
  for (size_t i = 0; i < numLines; i++) {
    getline(file, line);
    points[i] = lineToPoint(line, delim, numSplits);
  }
  return points;
}

