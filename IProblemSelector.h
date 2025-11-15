#ifndef IPROBLEM_SELECTOR_H
#define IPROBLEM_SELECTOR_H

#include "IProblem.h"
#include "Constraint.h"

#include <vector>
#include <memory>


class IProblemSelector {
public:
    virtual ~IProblemSelector() = default;

    virtual std::vector<std::shared_ptr<IProblem>> select(
        std::vector<std::shared_ptr<IProblem>>& bank,
        const std::vector<std::shared_ptr<Constraint>>& constraints,
        int numProblems
    ) = 0;
};

#endif