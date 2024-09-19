#include "StringCalculator.h"
#include <sstream>
#include <algorithm>
#include <numeric>
#include <regex>

// Converts string to an integer
int StringCalculator::toInt(const std::string& number) {
    return std::stoi(number);
}

// Adds up numbers from the input string
int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string delimiter = ",|\n";
    std::string input = numbers;
    
    // Custom delimiter case
    if (numbers.substr(0, 2) == "//") {
        delimiter = getCustomDelimiter(numbers);
        input = numbers.substr(numbers.find("\n") + 1);
    }

    // Parse numbers and validate
    std::vector<int> nums = parseNumbers(input, delimiter);
    validateNumbers(nums);

    // Ignore numbers greater than 1000
    nums.erase(std::remove_if(nums.begin(), nums.end(), [](int n){ return n > 1000; }), nums.end());

    // Sum the numbers
    return std::accumulate(nums.begin(), nums.end(), 0);
}

// Helper to get custom delimiter
std::string StringCalculator::getCustomDelimiter(const std::string& input) {
    std::regex customDelimRegex("//(\\[.*?\\])+\n");
    std::smatch match;
    if (std::regex_search(input, match, customDelimRegex)) {
        std::string customDelimiters = match.str();
        customDelimiters.erase(0, 2); // Remove the "//"
        customDelimiters.pop_back();  // Remove the "\n"
        
        // Convert multiple delimiters to regex
        std::regex escapeRegex(R"([\[|\]])");
        customDelimiters = std::regex_replace(customDelimiters, escapeRegex, "");
        return customDelimiters;
    }
    return input.substr(2, input.find("\n") - 2);
}

// Parses input string into vector of integers
std::vector<int> StringCalculator::parseNumbers(const std::string& numbers, const std::string& delimiter) {
    std::vector<int> result;
    std::regex delimRegex(delimiter);
    std::sregex_token_iterator iter(numbers.begin(), numbers.end(), delimRegex, -1);
    std::sregex_token_iterator end;

    while (iter != end) {
        std::string token = *iter++;
        if (!token.empty()) {
            result.push_back(toInt(token));
        }
    }
    return result;
}

// Validates numbers and throws exception for negative numbers
void StringCalculator::validateNumbers(const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int num : numbers) {
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
