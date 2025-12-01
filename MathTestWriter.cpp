//#include "FancyTestWriter.h"
#include "IProblem.h"
#include <fstream>   
#include <iostream>  

#include "MathTestWriter.h"
#include "MathProblem.h"
#include <algorithm>

extern std::string CLASS;
extern std::string TERM;
extern std::string EXAM;
extern std::string TIME;
extern std::string TITLE;
extern std::string FORM;
extern int NUM_PROBLEMS; // Used in the header
extern std::string TEX_HEADER;
extern std::string CONTENT_HEADER;

void MathTestWriter::writeTest(
    const std::string& filename,
    const std::vector<std::shared_ptr<IProblem>>& problems_input
) 
{
    std::vector<std::shared_ptr<IProblem>> problems = problems_input; //temp working copy
    
    std::ofstream outputFile(filename); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        //return 1;
    }
    // sort short first long last
    std::stable_partition(problems.begin(), problems.end(), [](const std::shared_ptr<IProblem>& p) {
        // islong? downcast check
        if (const auto* prob = dynamic_cast<const MathProblem*>(p.get())) {
            //return TRUE for SHORT problems, those  go to front
            return !prob->getIsLong(); 
        }
        return true; 
    });


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
    int shortCount = 0; //for page
    for (auto& problem : problems) {
        const auto* mathProb = dynamic_cast<const MathProblem*>(problem.get());
        if (!mathProb) continue;

        if (mathProb->getIsLong() ) {       // Start a new page before for LONG problems 
            outputFile << "\\pagebreak\n\n"; // 
            shortCount = 0; // reset count since isLong starts a new page
        } else {                                 // short problem, 2 per page at most logic
            shortCount++;
            if (shortCount % 2 != 0) {  // first short problem on page needs a new page
                outputFile << "\\pagebreak\n\n"; 
            } 
            else { // stay on page for second prob, insert vspace
                outputFile << "\\vspace{350pt}\n\n"; 
            }
        }
        outputFile << "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
        outputFile << problem->getQuestion(); //change to ->
        outputFile << "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";
        //problem_number += 1;
    }

    // End the file
    outputFile << "\\end{enumerate}\n\\end{document}";
    outputFile.close();



}