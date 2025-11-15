#ifndef IPROBLEM_H
#define IPROBLEM_H

#include <string>

class IProblem {
public:
    virtual ~IProblem() = default;
    virtual std::string getQuestion() const = 0;
    virtual std::string getAnswer()   const = 0;

};

#endif