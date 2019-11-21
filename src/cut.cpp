#include "cut.h"

void Cut::setA(std::vector<int> A)
{
    _A = A;
}

void Cut::setST(vector_of_pairs stList)
{
    _stList = stList;
}

void Cut::setCost(double cost)
{
    _cost = cost;
}

void Cut::setW(std::vector<std::vector<double>> W)
{
    _W = W;
    _dim = W.size();
}

void Cut::findEdges()
{
    std::vector<bool> visited(_dim);
    for (auto &ai : _A)
    {
        this->_traceBack(ai, visited);
    }

    for (int i = 0; i < _dim; ++i)
    {
        for (int j = 0; j < _dim; ++j)
            if (visited[i] && !visited[j] && _W[i][j] > -1)
            {
                _colors.insert(_W[i][j]);
                std::pair<int, int> edge = std::make_pair(i, j);
                _edges.push_back(edge);
            }
    }
}

void Cut::_traceBack(int val, std::vector<bool> &visited)
{
    visited[val] = true;
    for (auto &st_pair : _stList)
    {
        if (val == st_pair.first)
        {
            this->_traceBack(st_pair.second, visited);
            _A.push_back(st_pair.second);
        }
    }
}
