#ifndef MIN_CUT_H_
#define MIN_CUT_H_

#include <limits>
#include "min_cut_phase.h" // Cut
#include "cut.h"

Cut minCut(std::vector<std::vector<double>>, int, int);

#endif // MIN_CUT_H_