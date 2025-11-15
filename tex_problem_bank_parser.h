#ifndef TEX_PROBLEM_BANK_PARSER_H
#define TEX_PROBLEM_BANK_PARSER_H

#include "problem_bank_parser.h"
#include "problem.h"
#include <regex>
#include <fstream>
#include <sstream>

class TexProblemBankParser : public ProblemBankParser {
public:
    std::vector<std::shared_ptr<IProblem>> parse(const std::string& filename) override;
};

#endif