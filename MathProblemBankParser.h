#ifndef MATH_PROBLEM_BANK_PARSER_H
#define MATH_PROBLEM_BANK_PARSER_H



#include "problem_bank_parser.h"
#include "MathProblem.h"


#include <regex>
#include <fstream>
#include <sstream>

class MathProblemBankParser : public ProblemBankParser 
{
    public:
        std::vector<std::shared_ptr<IProblem>> parse(const std::string& filename) override;
};

#endif // everything is very loud