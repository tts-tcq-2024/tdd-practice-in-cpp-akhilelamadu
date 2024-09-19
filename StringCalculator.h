
#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::vector<int> parseNumbers(const std::string& numbers, const std::string& delimiter);
    int toInt(const std::string& number);
    std::string getCustomDelimiter(const std::string& input);
    void validateNumbers(const std::vector<int>& numbers);
};

#endif
