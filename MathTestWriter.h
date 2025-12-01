#ifndef MATH_TEST_WRITER_H
#define MATH_TEST_WRITER_H

#include "ITestWriter.h" 
#include "MathProblem.h"
class MathTestWriter : public ITestWriter {
    private:
    public:
        void writeTest(
            const std::string& filename,
            const std::vector<std::shared_ptr<IProblem>>& problems
        ) override
        
        
;};

#endif