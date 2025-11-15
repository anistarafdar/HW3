#ifndef PROBLEM_BANK_PARSER_H
#define PROBLEM_BANK_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "IProblem.h"

class ProblemBankParser {
public:
    virtual std::vector<std::shared_ptr<IProblem>> parse(const std::string& filename) = 0;
    virtual ~ProblemBankParser() = default;
};

#endif