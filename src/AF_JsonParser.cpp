#include "AF_JsonParser.h"
#include <sstream>
#include <fstream>

// Function to remove whitespaces from a string
// input: A string containing any number of whitespaces
// returns: A new string with all whitespaces removed
std::string removeWhitespaces(const std::string& input) {
    std::string output;
    for (char c : input) {
        if (!std::isspace(c)) {
            output += c;
        }
    }
    return output;
}

// Function to parse a JSON-like key-value format
// input: A string containing key-value pairs separated by commas
// returns: A map containing the key-value pairs extracted from the input string
std::map<std::string, std::string> parseKeyValuePairs(const std::string& input) {
    std::map<std::string, std::string> keyValuePairs;
    std::stringstream ss(input);
    std::string line;

    // Read the input string line by line, using ',' as the delimiter
    while (std::getline(ss, line, ',')) {
        size_t colonPos = line.find(':');
        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);

        // Remove whitespaces from the key and value
        key = removeWhitespaces(key);
        value = removeWhitespaces(value);

        // Add the key-value pair to the map
        keyValuePairs[key] = value;
    }

    return keyValuePairs;
}
