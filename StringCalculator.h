#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::string delimiter = ",|\n";  // Initialised with Default delimiters
    std::string numberString;

    std::vector<int> parsedNumbers;

    void ExtractNumbersAndDelimiters(const std::string& input);
    void setCustomDelimiter(const std::string& input);
    void extractNumberString(const std::string& input);
    void parseNumbers();

    
    size_t findNextDelimiter(size_t startPos) const;
    void parseSingleNumber(size_t startPos, size_t pos);

    void validateNumbers();
    void checkForNegatives();
    std::vector<int> gatherNegatives() const;
    std::string buildNegativeErrorMessage(const std::vector<int>& negatives) const;
    std::vector<int> filterLargeNumbers();
    int convertToInt(const std::string& number);
    int sumOfNumbers();
};

#endif
