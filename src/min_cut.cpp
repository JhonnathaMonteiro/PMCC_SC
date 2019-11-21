#include "min_cut.h"

Cut minCut(std::vector<std::vector<double>> G, int a, int dim)
{
    Cut bestCut;
    vector_of_pairs stList;
    bestCut.setCost(std::numeric_limits<double>::infinity());

    std::vector<int> V;
    for (int col = 0; col < dim; ++col)
    {
        if (col == a)
            continue;
        V.push_back(col);
    }

    std::vector<std::vector<double>> C = G;

    Cut cut_of_phase;
    for (int i = 0; i < dim - 1; ++i)
    {
        cut_of_phase = minCutPhase(C, a, dim, V, stList);
        if (cut_of_phase.getCost() < bestCut.getCost())
        {
            bestCut = cut_of_phase;
        }
    }

    bestCut.setW(G);
    bestCut.findEdges();

    return bestCut;
}