#include "ShuffleSelector.h"
#include <algorithm> 

ShuffleSelector::ShuffleSelector() : gen(std::random_device{}()) {}

std::vector<std::shared_ptr<IProblem>> ShuffleSelector::select( std::vector<std::shared_ptr<IProblem>>& bank,
                                                                const std::vector<std::shared_ptr<Constraint>>& constraints,
                                                                    int NUM_PROBLEMS
) 

{
    std::vector<std::shared_ptr<IProblem>> test;
    while (true) {
        std::shuffle(bank.begin(), bank.end(), gen);
        test.assign(bank.begin(), bank.begin() + NUM_PROBLEMS);

        bool valid = true;
        for (auto& c : constraints) {
            if (!c->isSatisfied(test)) {
                valid = false;
                break;
            }
        }
        if (valid) break;
    }
    return test;
}