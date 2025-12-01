#include "MathProblem.h"

#include <regex>
#include <iostream>
#include <stdexcept>
#include <algorithm> 

// i wanna fix this b
//const std::string MATH_FORMAT = "^([\\s\\S]*)\\\\answer\\{([\\s\\S]*)\\}[\s\\S]*\\\\topic\\{(.*)\\}[\s\\S]*\\\\author\\{(.*)\\}[\s\\S]*\\\\isLong\\{(.*)\\}";
const std::string MATH_FORMAT = "([\\s\\S]*?)\\\\answer\\{([\\s\\S]*?)\\\\}[\\s\\S]*\\\\topic\\{(.*?)\\\\}[\\s\\S]*\\\\author\\{(.*?)\\\\}[\\s\\S]*\\\\isLong\\{(.*?)\\\\}";
// this doesnt fucking work
//const std::string MATH_FORMAT = 
//    "^([\\s\\S]*?)\\\\answer\\{([\\s\\S]*?)\\\\}[\\s\\S]*\\\\topic\\{(.*?)\\\\}[\\s\\S]*\\\\author\\{(.*?)\\\\}[\\s\\S]*\\\\isLong\\{(.*?)\\\\}[\\s\\S]*$";


const std::regex MATH_RE(MATH_FORMAT);

// self explanatory
std::string MathProblem::getQuestion() const { return question; }
std::string MathProblem::getAnswer() const { return answer; }
std::string MathProblem::getTopic() const { return topic; }
std::string MathProblem::getAuthor() const { return author; }
bool MathProblem::getIsLong() const { return isLong; }
//dude you got to be fucking kidding me a goto is disgusting i hate this
MathProblem::MathProblem(std::string rawProblem) {
    //  TRIM LEADING WHITESPACE
    std::string isLongStr;
    size_t first_char = rawProblem.find_first_not_of(" \t\n\r");
    if (first_char != std::string::npos) {
        rawProblem = rawProblem.substr(first_char);
    }

    //delimiters used in math_problems.tex
    const std::string ANS_TAG = "\\answer{";
    const std::string TOPIC_TAG = "\\topic{";
    const std::string AUTHOR_TAG = "\\author{";
    const std::string ISLONG_TAG = "\\isLong{";
    const std::string END_TAG = "}";

    // extraction
    std::string workingStr = rawProblem;
    size_t start, end;
    
    //EXTRACT QUESTION question is everything before \answer{
    end = workingStr.find(ANS_TAG);
    if (end == std::string::npos) goto parse_error;
    question = workingStr.substr(0, end);
    workingStr = workingStr.substr(end); // workingStr to start at \answer{

    // EXTRACT ANSWER
    start = workingStr.find(ANS_TAG) + ANS_TAG.length();
    end = workingStr.find(END_TAG, start);
    if (end == std::string::npos) goto parse_error;
    answer = workingStr.substr(start, end - start);
    workingStr = workingStr.substr(end); // workingStr to start after the closing brace

    //EXTRACT TOPIC
    start = workingStr.find(TOPIC_TAG) + TOPIC_TAG.length();
    end = workingStr.find(END_TAG, start);
    if (end == std::string::npos) goto parse_error;
    topic = workingStr.substr(start, end - start);
    workingStr = workingStr.substr(end); // workingStr to start at \answer{

    //EXTRACT AUTHO
    start = workingStr.find(AUTHOR_TAG) + AUTHOR_TAG.length();
    end = workingStr.find(END_TAG, start);
    if (end == std::string::npos) goto parse_error;
    author = workingStr.substr(start, end - start);
    workingStr = workingStr.substr(end); // workingStr to start at \answer{

    // EXTRACT ISLONG 
    start = workingStr.find(ISLONG_TAG) + ISLONG_TAG.length();
    end = workingStr.find(END_TAG, start);
    if (end == std::string::npos) goto parse_error;
    isLongStr = workingStr.substr(start, end - start); // workingStr to start at \answer{
    
    // Convert to boolean
    std::transform(isLongStr.begin(), isLongStr.end(), isLongStr.begin(), ::tolower);
    isLong = (isLongStr == "true");

    return; 

parse_error: // dont like this but i need to see
    std::cerr << "invalid problem format / tag missing): " << rawProblem.substr(0, 64) << "...\n";
    throw std::runtime_error("Invalid problem format");
}




/*
// not self explanatory 
MathProblem::MathProblem(std::string rawProblem) {
    // please let me go to bed
    size_t first_char = rawProblem.find_first_not_of(" \t\n\r");
    if (first_char != std::string::npos) {
        //trim the leading garbage
        rawProblem = rawProblem.substr(first_char);
    }

    std::cerr << "debug text, Attempting to match RAW INPUT START\n";
    std::cerr << rawProblem.substr(0, 100) << "\n";
    std::cerr << "debug text, RAW INPUT END\n";

    std::smatch match;
    

    if (!std::regex_search(rawProblem, match, MATH_RE)) {
        std::cerr << "Invalid problem format: " << rawProblem.substr(0, 64) << "...\n";
        throw std::runtime_error("Invalid problem format");
    }
    
    
    question = match.str(1);
    answer = match.str(2);
    topic = match.str(3);
    author = match.str(4);
    
    // string to bool
    std::string isLongStr = match.str(5); // convert to lower case, todo find a more pretty way to do this, maybe al ibrary
    std::transform(isLongStr.begin(), isLongStr.end(), isLongStr.begin(), ::tolower); // holy shit dude 
    isLong = (isLongStr == "true");

}// qa and topic and author... is long too, diff?
*/