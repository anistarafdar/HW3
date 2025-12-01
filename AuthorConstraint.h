#ifndef AUTHOR_CONSTRAINT_H
#define AUTHOR_CONSTRAINT_H

#include "Constraint.h"
#include "MathProblem.h" // aiiuugh
#include <map>
#include <string>
#include <vector>
#include <memory> 

class AuthorConstraint : public Constraint {
    private:
        int minCount;
        int maxCount;
        std::vector<std::string> allAuthors; // unique authors

    public:
        AuthorConstraint(int minC, int maxC, std::vector<std::string> authors)
            : minCount(minC), maxCount(maxC), allAuthors(std::move(authors)) {}

        // within range? every authors prob
        bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
};

#endif