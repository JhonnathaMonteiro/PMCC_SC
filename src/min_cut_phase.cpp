#include <iostream>

#include "min_cut_phase.h"

void _contractEdges(int v1, int v2, std::vector<std::vector<double>> &C, int dim, Cut &cut_of_phase)
{
    double cutCost = 0;
    for (int i = 0; i < dim; ++i)
    {
        if (C[v2][i] > 0)
        {
            cutCost += C[v2][i];
            if (i != v1)
            {
                C[v1][i] = C[i][v1] += C[v2][i];
            }

            C[v2][i] = C[i][v2] = 0;
        }
    }
    C[v1][v2] = C[v2][v1] = 0;
    cut_of_phase.setCost(cutCost);
}

Cut minCutPhase(std::vector<std::vector<double>> &C,
                int a,
                int dim,
                std::vector<int> &V,
                vector_of_pairs &stList)
{

    Cut cut_of_phase;
    int s, t;
    std::vector<int> A, Vcopy;
    A.push_back(a);

    // construindo a fibonacci heap
    FibonacciHeap<double> fbHeap;
    for (auto &vi : V)
    {
        fbHeap.insert(vi, -C[a][vi]); // -C para ExtractMin -> ExtractMax
        Vcopy.push_back(vi);
    }

    while (!fbHeap.isEmpty())
    {

        a = fbHeap.extractMin();
        A.push_back(a);
        Vcopy.erase(std::remove(Vcopy.begin(), Vcopy.end(), a), Vcopy.end());

        // Update fbHeap
        for (auto &col : Vcopy)
        {
            if (C[a][col] > 0)
            {
                node<double> *n = fbHeap.find(col);
                fbHeap.decreaseKey(n, -C[a][col] + n->getValue());
            }
        }
    }

    // srink s-t
    s = *(A.rbegin() + 1);
    t = *(A.rbegin());
    std::pair<int, int> st_pair = std::make_pair(s, t);

    _contractEdges(s, t, C, dim, cut_of_phase);

    V.erase(std::remove(V.begin(), V.end(), t), V.end());
    A.erase(std::remove(A.begin(), A.end(), t), A.end());

    cut_of_phase.setA(A);
    cut_of_phase.setST(stList);
    stList.push_back(st_pair);

    return cut_of_phase;
}