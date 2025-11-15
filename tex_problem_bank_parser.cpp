#include <iostream> 
#include <fstream>  

#include "tex_problem_bank_parser.h"
/*
std::vector<std::shared_ptr<IProblem>> TexProblemBankParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();


    if (content.length() == 0) {
    std::cerr << "!!! DEBUG: File is empty!" << std::endl;
    return {}; }

    std::vector<std::shared_ptr<IProblem>> problems;
    std::string delimiter = "\\item";
    //std::string delimiter = "\\\\item"; //bro
    //std::string delimiter = "\\\\\\\\item";
    size_t pos = 0;

    while ((pos = content.find(delimiter)) != std::string::npos) {
     
    }

    return problems;
}
*/ 

//ge 
std::vector<std::shared_ptr<IProblem>> TexProblemBankParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "!!! DEBUG: FAILED TO OPEN FILE: " << filename << std::endl;
        return {};
    }
    //std::cerr << "--- DEBUG: DEBUG: SUCCESS TO OPEN FILE: " << filename << std::endl;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    //std::cerr << "--- DEBUG:" << content.length() << " bytes from file." << std::endl;

    std::vector<std::shared_ptr<IProblem>> problems;
    

    const std::string start_delimiter = "\\begin{enumerate}";
    const std::string end_delimiter = "\\end{enumerate}";
    const std::string item_delimiter = "\\item"; 

    size_t start_pos = content.find(start_delimiter);
    size_t end_pos = content.find(end_delimiter);

    if (start_pos == std::string::npos || end_pos == std::string::npos) {
        std::cerr << "!!! DEBUG: CANT FIND start_delimiter or end_delimiter: \\begin{enumerate} or \\end{enumerate}" << std::endl;
        return {};
    }

    start_pos += start_delimiter.length();
    std::string problem_content = content.substr(start_pos, end_pos - start_pos);

    size_t current_pos = problem_content.find(item_delimiter);
    size_t next_pos = 0;

    if (current_pos == std::string::npos) {
         std::cerr << "!!! DEBUG: Found 0 \\item delimiters." << std::endl;
         return {};
    }

    while (current_pos != std::string::npos) {
        // from the current \item, find the next one
        next_pos = problem_content.find(item_delimiter, current_pos + 1);

        std::string rawProblem;
        size_t start_of_problem = current_pos + item_delimiter.length();

        // last problem finder
        if (next_pos != std::string::npos) {
            // not last prob.
            rawProblem = problem_content.substr(start_of_problem, next_pos - start_of_problem);
        } else {
            // last problem. Extract from this \item to the end.
            rawProblem = problem_content.substr(start_of_problem);
        }

        // Pass the clean problem string to the constructor
        problems.push_back(std::make_shared<Problem>(rawProblem));
        //std::cerr << "--- DEBUG: Parsed 1 problem." << std::endl;

        // Move to the next item for the next loop
        current_pos = next_pos;
    }
    

    std::cerr << "!! DEBUG: Total problems parsed: " << problems.size() << std::endl;
    return problems;
}