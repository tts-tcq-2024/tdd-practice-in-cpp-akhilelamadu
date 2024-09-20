#include "StringCalculator.h"
#include <sstream>
#include <algorithm>
#include <numeric>

// Adds up numbers from the input string
int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    // Parse input and extract numbers and delimiters
    parseInput(numbers);
    
    // Parse and filter numbers
    parseNumbers();
    validateNumbers();
    
    // Filter large numbers
    parsedNumbers = filterLargeNumbers();

    // Return the sum
    return sumNumbers();
}

// Parse the input string to set delimiter and number string
void StringCalculator::parseInput(const std::string& input) {
    if (input.substr(0, 2) == "//") {
        setCustomDelimiter(input);
        extractNumberString(input);
    } else {
        numberString = input;
    }
}

// Set custom delimiter if provided
void StringCalculator::setCustomDelimiter(const std::string& input) {
    size_t newlinePos = input.find("\n");
    std::string delimiterPart = input.substr(2, newlinePos - 2);

    // Handle case with multiple delimiters between square brackets
    if (delimiterPart[0] == '[') {
        delimiter.clear();
        size_t startPos = 1, endPos = 0;
        while ((endPos = delimiterPart.find(']', startPos)) != std::string::npos) {
            delimiter += delimiterPart.substr(startPos, endPos - startPos);
            startPos = endPos + 2;  // skip past "][" or end
        }
    } else {
        delimiter = delimiterPart;  // Single delimiter case
    }
}

// Extract the part of the string with numbers, excluding the delimiter line
void StringCalculator::extractNumberString(const std::string& input) {
    numberString = input.substr(input.find("\n") + 1);
}

// Converts string to an integer
int StringCalculator::toInt(const std::string& number) {
    return std::stoi(number);
}

// Parses the number string into a vector of integers
void StringCalculator::parseNumbers() {
    parsedNumbers.clear();
    size_t pos = 0, startPos = 0;

    while ((pos = numberString.find_first_of(delimiter, startPos)) != std::string::npos) {
        std::string token = numberString.substr(startPos, pos - startPos);
        if (!token.empty()) {
            parsedNumbers.push_back(toInt(token));
        }
        startPos = pos + 1;
    }

    if (startPos < numberString.length()) {
        parsedNumbers.push_back(toInt(numberString.substr(startPos)));
    }
}

// Validate numbers, checking for negative values
void StringCalculator::validateNumbers() {
    checkForNegatives();
}

// Check for negative numbers and throw an exception if any are found
void StringCalculator::checkForNegatives() {
    std::vector<int> negatives;
    for (int num : parsedNumbers) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }

    if (!negatives.empty()) {
        std::string errorMsg = "negatives not allowed: ";
        for (int neg : negatives) {
            errorMsg += std::to_string(neg) + " ";
        }
        throw std::runtime_error(errorMsg);
    }
}

// Filters out numbers greater than 1000
std::vector<int> StringCalculator::filterLargeNumbers() {
    std::vector<int> filtered;
    std::copy_if(parsedNumbers.begin(), parsedNumbers.end(), std::back_inserter(filtered), [](int n){ return n <= 1000; });
    return filtered;
}

// Sums up the numbers in the vector
int StringCalculator::sumNumbers() {
    return std::accumulate(parsedNumbers.begin(), parsedNumbers.end(), 0);
}
