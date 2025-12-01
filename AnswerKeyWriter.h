#ifndef ANSWER_KEY_WRITER_H

#define ANSWER_KEY_WRITER_H



#include "ITestWriter.h" 





class AnswerKeyWriter : public ITestWriter {
    public:
        void writeTest(
            const std::string& filename,
            const std::vector<std::shared_ptr<IProblem>>& problems
        ) override;
};



#endif