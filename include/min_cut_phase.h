#ifndef MIN_CUT_PHASE_H_
#define MIN_CUT_PHASE_H_

#include <vector>
#include <algorithm> // erase

#include "fibonacci_heap.h"
#include "cut.h"

Cut minCutPhase(std::vector<std::vector<double>> &, int, int, std::vector<int> &, vector_of_pairs &);

#endif // MIN_CUT_PHASE_H_