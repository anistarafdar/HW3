#include "FastSelector.h"
#include "MathProblem.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

/*/
// helper to see if a problem exceeds a max
bool checkMaxConstraints(
    const std::vector<std::shared_ptr<IProblem>>& currentTest,
    const std::shared_ptr<IProblem>& candidate,
    const std::vector<std::shared_ptr<Constraint>>& constraints)

{
    //build a list
    std::vector<std::shared_ptr<IProblem>> tempTest = currentTest;
    tempTest.push_back(candidate);

    // check all constrants 
    for (const auto& c : constraints) {
        if (!c->isSatisfied(tempTest)) {
            return false;
        }
    }
    return true;
} 
*/
FastSelector::FastSelector() : gen(std::random_device{}()) {}

std::vector<std::shared_ptr<IProblem>> FastSelector::select(
    std::vector<std::shared_ptr<IProblem>>& bank,
    const std::vector<std::shared_ptr<Constraint>>& constraints,
    int numProblems
) {
    // restarts if the final problem set fails minimum constraints
    bool finalCheckPassed = false;
    std::vector<std::shared_ptr<IProblem>> test;

    // use a fixed max limits per assignments specs (not scalable by not the hardest to fix up)
    const int ABSOLUTE_MAX_TOPIC_AUTHOR = 2;
    const int ABSOLUTE_MAX_LONG = 4;
    
    do {
        test.clear(); //pls dont put me in hell
        
        // shuffle the entire problem bank for randomness as per stupid alg
        std::shuffle(bank.begin(), bank.end(), gen);
        
        // maps to track counts of in the CURRENT  test 
        std::map<std::string, int> currentAuthorCounts;
        std::map<std::string, int> currentTopicCounts;
        int currentLongCount = 0;

        // filter against max
        for (const auto& problem : bank) {
            
            // if final size is reached, stop
            if (test.size() >= static_cast<size_t>(numProblems)) break;
            
            // down cast the candidate to access its metadata
            const auto* candidate = dynamic_cast<const MathProblem*>(problem.get());
            if (!candidate) continue; // jic

            // max constraint checker, greedy filter
            
            bool authorMaxViolated = currentAuthorCounts[candidate->getAuthor()] >= ABSOLUTE_MAX_TOPIC_AUTHOR;
            bool topicMaxViolated = currentTopicCounts[candidate->getTopic()] >= ABSOLUTE_MAX_TOPIC_AUTHOR;            
            bool longMaxViolated = candidate->getIsLong() && (currentLongCount >= ABSOLUTE_MAX_LONG);            
            if (authorMaxViolated || topicMaxViolated || longMaxViolated) {
                continue; //if ANYTHING got violated then try again
            }

            // nothing violated, push it back
            test.push_back(problem);
            
            // house keep the current counts for the next iteration
            currentAuthorCounts[candidate->getAuthor()]++;
            currentTopicCounts[candidate->getTopic()]++;
            if (candidate->getIsLong()) { currentLongCount++; }
        }
        
        // ensure minimums checked
        //  if test size is 10, run final check
        if (test.size() == static_cast<size_t>(numProblems)) {
            finalCheckPassed = true; // innocent till proven guilty
            
            // check ALL constraints min and max
            for (const auto& c : constraints) {
                if (!c->isSatisfied(test)) {
                    finalCheckPassed = false;
                    // std::cerr << "DEBUG!!! Restarting: failed final constraint check in min check.\n";  //ingdebug
                    break;
                }
            }
        } else {
            finalCheckPassed = false; // some how didnt catch ten problems!
        }

    } while (!finalCheckPassed); // restart until we pass checks, hopefukky not infinute.
    
    return test;
}