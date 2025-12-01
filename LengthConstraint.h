#ifndef LENGTH_CONSTRAINT_H
#define LENGTH_CONSTRAINT_H

#include "Constraint.h"
#include "MathProblem.h" 
// downcast and getter for isLong

class LengthConstraint : public Constraint {
    private:
        int minCount;
        int maxCount;
    public:
        LengthConstraint(int minC, int maxC) : minCount(minC), maxCount(maxC) {}

        bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
};

#endif