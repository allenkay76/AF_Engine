// SimpleJsonParser.h
//Made by chatGTP4 and Allen Kay
#pragma once

#include <string>
#include <map>


// Function to remove whitespaces from a string
std::string removeWhitespaces(const std::string& input);

// Function to parse a JSON-like key-value format
std::map<std::string, std::string> parseKeyValuePairs(const std::string& input);
