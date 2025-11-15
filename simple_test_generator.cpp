#include <ranges>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <map>
#include <set>
#include "problem.h"
#include "IProblem.h"
#include "tex_problem_bank_parser.h"
#include "constraint.h"
#include <memory> //trying to use smart pointers for future profingh
#include "IProblemSelector.h" 
#include "ShuffleSelector.h"  
#include "ITestWriter.h"      
#include "SimpleTestWriter.h" 
// ****************************************************************************
// Configuration details

// Title to be printed at the beginning of the test
std::string TITLE = "Arithmetic Test";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "simple_test.tex";

// Constraints on the problem choice.
int NUM_PROBLEMS = 20; // The test must have 20 problems.
int MIN_TOPIC = 3; // Each topic must be covered 
int MAX_TOPIC = 7; // by 3-7 problems.
int MIN_DIFFICULTY = 65; // Total difficulty (using the difficulty defined 
int MAX_DIFFICULTY = 75; // in the problem bank) must be 65-75.

// tex files to include in the test file
std::string TEX_HEADER = "simple_tex_header.tex";
std::string CONTENT_HEADER = "simple_content_header.tex";

// create constants

// ****************************************************************************
/*
// Check whether a proposed test is valid according to the above constraints.
bool valid(std::vector<Problem> test, std::set<std::string> topics) {
    // Initialize metrics
    int difficulty = 0;
    std::map<std::string, int> topicCounts;
    for (std::string topic : topics) {
        topicCounts[topic] = 0;
    }

    // Calculate the metrics
    for (Problem p : test) {
        difficulty += p.getDifficulty();
        topicCounts[p.getTopic()] += 1;
    }

    // Check the metrics
    if (difficulty < MIN_DIFFICULTY || difficulty > MAX_DIFFICULTY) {
        return false;
    }
    for (std::string topic : topics) {
        int count = topicCounts[topic];
        if (count < MIN_TOPIC || count > MAX_TOPIC) {
            return false;
        }
    }
    return true;
}

// Given a bank of possible test problems, return randomly-chosen 
// problems that form a valid test, according to the contraints above.
std::vector<Problem> testProblems(std::vector<Problem> bank) {
    // Determine the topics covered on the test
    std::set<std::string> topics;
    for (Problem p : bank) {
        topics.insert(p.getTopic());
    }

    // Used for random generation
    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::shuffle(bank.begin(), bank.end(), gen);
        std::vector<Problem> testProblems(bank.begin(), bank.begin() + NUM_PROBLEMS);
        if (valid(testProblems, topics)) {
            return testProblems;
        }
    }
}
*/

int main() {
    // Read in problem list and convert to Problem objects
    //std::vector<Problem> bank = Problem::problemList(BANK);

    
    TexProblemBankParser parser;
    ShuffleSelector selector;
    SimpleTestWriter writer;
    //auto bank = parser.parse(BANK);
    std::vector<std::shared_ptr<IProblem>> bank = parser.parse(BANK);

    
    // got problems?
    if (bank.size() < static_cast<size_t>(NUM_PROBLEMS)) {
        std::cerr << "Not enough problems in bank (" << bank.size()
                << ") to pick " << NUM_PROBLEMS << ".\n";
        return 1;
    }

    // build topic list from bank
    std::set<std::string> topicSet;
    for (const auto& p : bank) {
        if (const auto* pr = dynamic_cast<const Problem*>(p.get())) {
            topicSet.insert(pr->getTopic());
        }
    }
    std::vector<std::string> allTopics(topicSet.begin(), topicSet.end());

    ///constraiiinst
    std::vector<std::shared_ptr<Constraint>> constraints;
    constraints.push_back(std::make_shared<TopicConstraint>(MIN_TOPIC, MAX_TOPIC, allTopics));
    constraints.push_back(std::make_shared<DifficultyConstraint>(MIN_DIFFICULTY, MAX_DIFFICULTY));



    // Generate the test problems
    //std::vector<Problem> test = testProblems(bank);

    // ok this might sound crazy but i think it makes more sense to put the logic here for now (until it seems needed to make its own class file)
    // this selection algoritm is kinda part of the generators job. i think it might be "tidier" to move it to another class if i plan to use MUltIPLE selection algorithms without touching the generator
    // but i cant imagine how a math prof would really need this part of the spec to ever change, the way it does it now seems like the best way. agian, i hope this executive decision doesnt bite me in the ass
    // but if it does, its no big deal to move it in the future/
    // for now lets keep it simple and try to avoid over engineering where it probly isnt needed....., i dont antipciate big changes in selection logic.

    std::vector<std::shared_ptr<IProblem>> test = 
        selector.select(bank, constraints, NUM_PROBLEMS);
    /*
    // Open the file to write the test to
    std::ofstream outputFile(FILENAME); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    // Write the header to the file
    outputFile << "\\input{" << TEX_HEADER << "}\n";
    outputFile << "\\newcommand{\\testtitle}{" << TITLE << "}\n";
    outputFile << "\\input{" << CONTENT_HEADER << "}\n";

    // Write the problems to the file
    //for (Problem problem : test) {
    for (auto& problem : test) {
        outputFile << "\\item " << problem->getQuestion() << "\n";
    }

    // End the file
    outputFile << "\\end{enumerate}\n\\end{document}";
    outputFile.close();
    */
    writer.writeTest(FILENAME, test);
}