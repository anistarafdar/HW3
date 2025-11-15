
#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "IProblem.h"
#include "problem.h" // keep to use dynamic_cast to concrete Problem

// Base 
class Constraint {
public:
    virtual bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const = 0;
    virtual ~Constraint() = default;
};

//constraint topics enforce tht minCountand maxCount for each topic in the bank
class TopicConstraint : public Constraint {
    private:
        int minCount;
        int maxCount;
        std::vector<std::string> allTopics; // topics discovered from the bank
    public:
    TopicConstraint(int minC, int maxC, std::vector<std::string> topics)
        : minCount(minC), maxCount(maxC), allTopics(std::move(topics)) {}

    bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override {
        std::map<std::string, int> counts;
        for (const auto& t : allTopics) counts[t] = 0;

        for (auto& p : problems) {
            if (auto* prob = dynamic_cast<Problem*>(p.get())) {
                auto t = prob->getTopic();
                if (counts.find(t) != counts.end()) counts[t]++;
            }
        }

        for (const auto& kv : counts) {
            int c = kv.second;
            if (c < minCount || c > maxCount) return false;
        }
        return true;
    }
};

// constraint total difficulty in betw minDifficulty and maxDifficulty
class DifficultyConstraint : public Constraint {
private:
    int minDifficulty;
    int maxDifficulty;
public:
    DifficultyConstraint(int minD, int maxD) : minDifficulty(minD), maxDifficulty(maxD) {}

    bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override {
        int total = 0;
        for (auto& p : problems) {
            if (auto* prob = dynamic_cast<Problem*>(p.get())) {
                total += prob->getDifficulty();
            }
        }
        return total >= minDifficulty && total <= maxDifficulty;
    }
};

// i am caiught between two places... do i make this multiple files... 
// my next project after this is to extend the code to to create test generators for tests in new formats, with as few changes to existing code as possible. i am wondering how different it can be... and that if that difference warrants multiple constraint files... my fear with oop is over engineering

// if i decide to change my mind and make multiple classes in differnet folders and headers... this bad foresight can bite me in the back... but i have no way of knowing how much complciated it can beeeeeeeeeeeee 
#endif