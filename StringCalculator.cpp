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
    if (newlinePos != std::string::npos) {
        // Extract the delimiter starting from position 2 (after the "//") to the newline character
        delimiter = input.substr(2, newlinePos - 2);
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
    size_t startPos = 0;
    size_t pos = 0;

    // Parse each token from the numberString
    while ((pos = findNextDelimiter(startPos)) != std::string::npos) {
        parseSingleNumber(startPos, pos);
        startPos = pos + 1;
    }

    // Handle the last part of the string
    if (startPos < numberString.length()) {
        parseSingleNumber(startPos, numberString.length());
    }
}

// Helper function to find the next delimiter
size_t StringCalculator::findNextDelimiter(size_t startPos) const {
    return numberString.find_first_of(delimiter, startPos);
}

// Helper function to parse and add a single number from the substring
void StringCalculator::parseSingleNumber(size_t startPos, size_t pos) {
    std::string token = numberString.substr(startPos, pos - startPos);
    if (!token.empty()) {
        parsedNumbers.push_back(toInt(token));
    }
}


// Validate numbers, checking for negative values
void StringCalculator::validateNumbers() {
    checkForNegatives();
}

// Check for negative numbers and throw an exception if any are found
void StringCalculator::checkForNegatives() {
    std::vector<int> negatives = gatherNegatives();

    if (!negatives.empty()) {
        throw std::runtime_error(buildNegativeErrorMessage(negatives));
    }
}

// Gather all negative numbers from parsedNumbers
std::vector<int> StringCalculator::gatherNegatives() const {
    std::vector<int> negatives;
    for (int num : parsedNumbers) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
    return negatives;
}

// Build the error message for negative numbers
std::string StringCalculator::buildNegativeErrorMessage(const std::vector<int>& negatives) const {
    std::string errorMsg = "negatives not allowed: ";
    for (int neg : negatives) {
        errorMsg += std::to_string(neg) + " ";
    }
    return errorMsg;
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
