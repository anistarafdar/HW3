#ifndef MATH_PROBLEM_H
#define MATH_PROBLEM_H



#include "IProblem.h"
#include <string> ///



class MathProblem : public IProblem {
    public:
        // constructor - parsing logic
        explicit MathProblem(std::string rawProblem);

        // overridah
        std::string getQuestion() const override;
        std::string getAnswer()   const override;

        // getter for metadata
        std::string getTopic()  const; //  for connstraints?
        std::string getAuthor() const;
        bool        getIsLong() const;

    private:
        std::string question;
        std::string answer;
        std::string topic;
        std::string author;
        bool        isLong; ////
};

#endif // how 