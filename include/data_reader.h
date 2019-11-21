#ifndef DATA_PMCC_H_
#define DATA_PMCC_H_

#include <set>     // std::set
#include <utility> // std::pair std::make_pair
#include <vector>  // std::vector
#include <fstream> // std::fstream

template <class T>
class DataReader
{
private:
   int _V;
   int _L;
   int const default_value = -1;
   std::vector<std::vector<T>> _G;

public:
   DataReader(char *file_path);
   int getV() { return _V; }
   int getL() { return _L; }
   std::vector<std::vector<T>> getG() { return _G; }
};

template <class T>
DataReader<T>::DataReader(char *file_path)
{
   std::ifstream file(file_path);
   file >> _V >> _L;
   _G.resize(_V, std::vector<T>(_V, default_value));
   for (int row = 0; row < _V - 1; ++row)
   {
      for (int col = row + 1; col < _V; ++col)
      {
         file >> _G[row][col];
         _G[col][row] = _G[row][col];
      }
   }
}

#endif
