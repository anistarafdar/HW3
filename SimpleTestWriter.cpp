#include "SimpleTestWriter.h"
#include "IProblem.h"
#include <fstream>   
#include <iostream>  

extern std::string TITLE;
extern std::string TEX_HEADER;
extern std::string CONTENT_HEADER;
/* idk how to stop the compiler from being mad without changeing the stuff without making an interface but then it said dont make an interafce cuz a You don’t need to add a user interface. Currently, the program is hard-coded with various
pieces of configuration information (such as the filename of the problem bank and the
number of problems on the test, and optionally other information such as the name of the
course, the semester, and so on). Arguably, it would be preferable to let the user pass in
such information after compilation (either interactively, or as a command-line argument),
so that we don’t need to edit and recompile the code every time.
But I don’t want
this to turn into an assignment about user interface design; that would get complicated,
especially since the required configuration information will change depending on the test
style. As such, you may assume that the end users are fine with modifying a few hard-
coded constants. More specifically, you may assume that the end user is a math teacher:
we do not assume that the user has any knowledge of C++, but the user has enough
technical competence to edit a few clearly-labeled constants at the top of the source code
and follow instructions to recompile it.



// Title to be printed at the beginning of the test
std::string TITLE = "Arithmetic Test";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "simple_test.tex";
*/

void SimpleTestWriter::writeTest(const std::string& filename, const std::vector<std::shared_ptr<IProblem>>& problems)  {
    
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

    // Write the problems to the file
    //for (Problem problem : test) {
    for (auto& problem : problems) {
        outputFile << "\\item " << problem->getQuestion() << "\n";
    }

    // End the file
    outputFile << "\\end{enumerate}\n\\end{document}";
    outputFile.close();
}