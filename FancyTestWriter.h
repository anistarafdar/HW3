#ifndef FANCY_TEST_WRITER_H
#define FANCY_TEST_WRITER_H

#include "ITestWriter.h" 

class FancyTestWriter : public ITestWriter {
    private:
    public:
        void writeTest(
            const std::string& filename,
            const std::vector<std::shared_ptr<IProblem>>& problems
        ) override;};

#endif