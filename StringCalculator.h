#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::string delimiter = ",|\n";  // Default delimiters
    std::string numberString;        // Holds the part of the input with numbers

    std::vector<int> parsedNumbers;  // Parsed list of numbers

    void parseInput(const std::string& input);
    void setCustomDelimiter(const std::string& input);
    void extractNumberString(const std::string& input);
    void parseNumbers();
    void validateNumbers();
    void checkForNegatives();
    std::vector<int> gatherNegatives() const;
    std::string buildNegativeErrorMessage(const std::vector<int>& negatives) const;
    std::vector<int> filterLargeNumbers();
    int toInt(const std::string& number);
    int sumNumbers();
};

#endif
