#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>
#include "IProblem.h"

class Problem : public IProblem {
public:
    std::string getQuestion() const override;
    std::string getAnswer()   const override;
    std::string getTopic() const;
    int getDifficulty() const;

    explicit Problem(std::string rawProblem);

    // static std::vector<Problem> problemList(std::string filename);

private:
    std::string question;
    std::string answer;
    std::string topic;
    int difficulty;
    
};

#endif
