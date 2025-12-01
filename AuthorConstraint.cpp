#include "AuthorConstraint.h"
#include <iostream>

bool AuthorConstraint::isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    std::map<std::string, int> counts;
    for (const auto& a : allAuthors) {
        counts[a] = 0;
    }

    for (const auto& p : problems) {
        if (const auto* prob = dynamic_cast<const MathProblem*>(p.get())) {
            auto a = prob->getAuthor();
            
            // per author increment count
            if (counts.count(a)) {
                counts[a]++;
            }
        }
    }
    // map of author counts done
    // check if all author counts meet the min/max
    for (const auto& kv : counts) {
        int c = kv.second;
        if (c < minCount || c > maxCount) {
            return false;
        }
    }
    
    return true;
}