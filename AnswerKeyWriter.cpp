#include "AnswerKeyWriter.h"
#include "IProblem.h"
#include <fstream>   
#include <iostream>  

extern std::string TITLE;
extern std::string TEX_HEADER;
extern std::string CONTENT_HEADER;

void AnswerKeyWriter::writeTest(const std::string& filename, const std::vector<std::shared_ptr<IProblem>>& problems)  {
    
    // Open the file to write the test to
    std::ofstream outputFile(filename); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        //return 1;
    }

    // Write the header to the file
    outputFile << "\\input{" << TEX_HEADER << "}\n";
    outputFile << "\\newcommand{\\testtitle}{" << TITLE << "}\n";
    outputFile << "\\input{" << CONTENT_HEADER << "}\n";

    // Cchange for answerkey
    for (auto& problem : problems) {
        outputFile << "\\item \\question{" << problem->getQuestion() << "}\n"; //hide q
        outputFile << "\\answer{" << problem->getAnswer() << "}\n"; //ohyey
    }

    // End the file
    outputFile << "\\end{enumerate}\n\\end{document}";
    outputFile.close();
}