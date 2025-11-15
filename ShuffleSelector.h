
#ifndef SHUFFLE_SELECTOR_H
#define SHUFFLE_SELECTOR_H



#include "IProblemSelector.h"
#include <random>

class ShuffleSelector : public IProblemSelector {
public:
    std::vector<std::shared_ptr<IProblem>> select(
        std::vector<std::shared_ptr<IProblem>>& bank,
        const std::vector<std::shared_ptr<Constraint>>& constraints,
        int numProblems
    ) override;



    ShuffleSelector();


private:
    std::mt19937 gen; /*We should be able to change the algorithm used to select the problems at random.
Notice that the current implementation is very stupid! It shuffles the entire problem
2
bank just to select some problems, and then keeps re-shuffling until it gets problems
that match the constraints. */
};


#endif