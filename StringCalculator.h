#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::vector<int> parseNumbers(const std::string& numbers, const std::string& delimiter);
    std::string getCustomDelimiter(const std::string& input);
    std::string getNumberString(const std::string& input);
    int sumNumbers(const std::vector<int>& numbers);
    void validateNumbers(const std::vector<int>& numbers);
    std::vector<int> findNegativeNumbers(const std::vector<int>& numbers);
    void throwIfNegatives(const std::vector<int>& negatives);
    int toInt(const std::string& number);
    std::vector<int> filterLargeNumbers(const std::vector<int>& numbers);
};

#endif
