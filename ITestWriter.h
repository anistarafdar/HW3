#ifndef ITEST_WRITER_H
#define ITEST_WRITER_H

#include "IProblem.h"
//#include "Constraint.h"

#include <vector>
#include <memory>
#include <string>
// in case we want something other than simple and fancy, like maybe  a landscape template
class ITestWriter {
public:
    virtual ~ITestWriter() = default;
    virtual void writeTest(
        const std::string& filename,
        const std::vector<std::shared_ptr<IProblem>>& problems
    ) = 0;
};

#endif