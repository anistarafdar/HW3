#include "FancyTestWriter.h"
#include "IProblem.h"
#include <fstream>   
#include <iostream>  

extern std::string CLASS;
extern std::string TERM;
extern std::string EXAM;
extern std::string TIME;
extern std::string TITLE;
extern std::string FORM;
extern int NUM_PROBLEMS; // Used in the header
extern std::string TEX_HEADER;
extern std::string CONTENT_HEADER;

void FancyTestWriter::writeTest(
    const std::string& filename,
    const std::vector<std::shared_ptr<IProblem>>& problems
) 
{

    
    std::ofstream outputFile(filename); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        //return 1;
    }
    // Write the tex header to the file
    outputFile << "\\input{" << TEX_HEADER << "}\n";

    // Include the manually-entered information
    outputFile << "\\newcommand{\\class}{" << CLASS << "}\n";
    outputFile << "\\newcommand{\\term}{" << TERM << "}\n";
    outputFile << "\\newcommand{\\examno}{" << EXAM << "}\n";
    outputFile << "\\newcommand{\\dayeve}{" << TIME << "}\n";
    outputFile << "\\newcommand{\\formletter}{" << FORM << "}\n";
    outputFile << "\\newcommand{\\numproblems}{" << NUM_PROBLEMS << " }\n";
    outputFile << "\\newcommand{\\testtitle}{" << TITLE << "}\n";

    // Write the content header to the file
    outputFile << "\\input{" << CONTENT_HEADER << "}\n";

    // Write the problems to the file
    int problem_number = 1;
    for (auto& problem : problems) {
        if (problem_number % 2 == 1) {       // Start a new page before 
            outputFile << "\\pagebreak\n\n"; // each odd-numbered problem
        } else {                                 // Insert blank space before
            outputFile << "\\vspace{350pt}\n\n"; // each even-numbered problem
        }
        outputFile << "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
        outputFile << problem->getQuestion(); //change to ->
        outputFile << "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";
        problem_number += 1;
    }

    // End the file
    outputFile << "\\end{enumerate}\n\\end{document}";
    outputFile.close();



}