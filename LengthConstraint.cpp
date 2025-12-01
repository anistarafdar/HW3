#include "LengthConstraint.h"
#include <iostream>

bool LengthConstraint::isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int longCount = 0;
    
    for (const auto& p : problems) {
        if (const auto* prob = dynamic_cast<const MathProblem*>(p.get())) {
            if (prob->getIsLong()) { // so pesky
                longCount++;
            }
        }
    }

    // check in range?
    return longCount >= minCount && longCount <= maxCount;
}