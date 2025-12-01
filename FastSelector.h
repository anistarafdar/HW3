#ifndef FAST_SELECTOR_H
#define FAST_SELECTOR_H

#include "IProblemSelector.h"
#include <random>
#include <vector>

class FastSelector : public IProblemSelector {
    public:
        FastSelector();

        std::vector<std::shared_ptr<IProblem>> select(
            std::vector<std::shared_ptr<IProblem>>& bank,
            const std::vector<std::shared_ptr<Constraint>>& constraints,
            int numProblems
        ) override;

    private:
        std::mt19937 gen;
};
#endif