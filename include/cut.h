#ifndef CUT_H_
#define CUT_H_

#include <vector>
#include <set>
#include <algorithm> // erase
#include "fibonacci_heap.h"

typedef std::vector<std::pair<int, int>> vector_of_pairs;

class Cut
{
private:
    void _traceBack(int, std::vector<bool> &);
    std::vector<std::vector<double>> _W;
    int _dim;
    double _cost;
    std::vector<int> _A;
    vector_of_pairs _stList;
    vector_of_pairs _edges;
    std::set<int> _colors;

public:
    vector_of_pairs getEdges() { return _edges; };
    std::set<int> getColors() { return _colors; }
    double getCost() { return _cost; }

    void setCost(double);
    void setW(std::vector<std::vector<double>>);
    void setA(std::vector<int>);
    void setST(vector_of_pairs);

    void findEdges();
};

#endif // CUT_H_
