#if __has_include("srell.hpp")
    #include "srell.hpp"
    #define USE_POWERFUL_REGEX 1
    #pragma message("SUCCESS: Compiling with powerful SRELL regex engine. Lookbehinds will work.")
#else
    #include <regex>
    #define USE_POWERFUL_REGEX 0
    #pragma message("WARNING: srell.hpp not found. Falling back to limited std::regex. Lookbehinds will NOT work.")
#endif

#include <algorithm>
#include <any>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// Function to escape special characters for regex
std::string escapeRegex(const std::string& str) {
    static const std::regex specialChars{R"([-[\]{}()*+?.,\^$|#\s])"};
    return std::regex_replace(str, specialChars, R"(\$&)");
}
// Function to split a string based on delimiters
std::vector<std::string> LoopParseFunc(const std::string& var, const std::string& delimiter1 = "", const std::string& delimiter2 = "") {
    std::vector<std::string> items;
    if (delimiter1.empty() && delimiter2.empty()) {
        // If no delimiters are provided, return a list of characters
        for (char c : var) {
            items.push_back(std::string(1, c));
        }
    } else {
        // Escape delimiters for regex
        std::string escapedDelimiters = escapeRegex(delimiter1 + delimiter2);
        // Construct the regular expression pattern for splitting the string
        std::string pattern = "[" + escapedDelimiters + "]+";
        std::regex regexPattern(pattern);
        std::sregex_token_iterator iter(var.begin(), var.end(), regexPattern, -1);
        std::sregex_token_iterator end;
        while (iter != end) {
            items.push_back(*iter++);
        }
    }
    return items;
}

// Print function for const char*
void print(const char* value) {
    std::cout << std::string(value) << std::endl;
}
// Handle signed 8-bit integers
void print(int8_t value) {
    std::cout << static_cast<int>(value) << std::endl;
}
// Handle unsigned 8-bit integers
void print(uint8_t value) {
    std::cout << static_cast<unsigned int>(value) << std::endl;
}
// Generic print function fallback
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

// Convert std::string to int
int INT(const std::string& str) {
    std::istringstream iss(str);
    int value;
    iss >> value;
    return value;
}

// Convert various types to std::string
std::string STR(int value) {
    return std::to_string(value);
}
// Convert various types to std::string
std::string STR(long long value) {
    return std::to_string(value);
}
std::string STR(float value) {
    return std::to_string(value);
}
std::string STR(double value) {
    return std::to_string(value);
}
std::string STR(size_t value) {
    return std::to_string(value);
}
std::string STR(bool value) {
    return value ? "1" : "0";
}
std::string STR(const char* value) {
    return std::string(value);
}
std::string STR(const std::string& value) {
    return value;
}

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

std::string FileRead(const std::string& path) {
    // This function relies on <fstream>, which is already in your global includes.
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open the file: " + path);
    }
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + '\n';
    }
    file.close();
    return content;
}

bool FileAppend(const std::string& content, const std::string& path) {
    std::ofstream file;
    // Open the file in append mode
    file.open(path, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file for appending." << std::endl;
        return false;
    }
    // Append the content to the file
    file << content;
    // Close the file
    file.close();
    return true;
}

bool FileDelete(const std::string& path) {
    return std::remove(path.c_str()) == 0;
}

size_t StrLen(const std::string& str) {
    return str.length();
}

std::string SubStr(const std::string& str, int startPos, int length = -1) {
    std::string result;
    size_t strLen = str.size();
    // Handle negative starting positions (counting from the end)
    if (startPos < 0) {
        startPos = strLen + startPos;
        if (startPos < 0) startPos = 0;  // Ensure it doesn't go beyond the start of the string
    }
    else {
        startPos -= 1; // Convert to 0-based index for internal operations
    }
    // Handle length
    if (length < 0) {
        length = strLen - startPos; // Length to the end of the string
    } else if (startPos + length > static_cast<int>(strLen)) {
        length = strLen - startPos; // Adjust length to fit within the string
    }
    // Extract the substring
    result = str.substr(startPos, length);
    return result;
}

std::string Trim(const std::string &inputString) {
    if (inputString.empty()) return "";
    size_t start = inputString.find_first_not_of(" \t\n\r\f\v");
    size_t end = inputString.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : inputString.substr(start, end - start + 1);
}

std::string StrReplace(const std::string &originalString, const std::string &find, const std::string &replaceWith) {
    std::string result = originalString;
    size_t pos = 0;
    while ((pos = result.find(find, pos)) != std::string::npos) {
        result.replace(pos, find.length(), replaceWith);
        pos += replaceWith.length();
    }
    return result;
}

std::string StringTrimLeft(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(numChars) : input;
}

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
}

std::string StrLower(const std::string &string) {
    std::string result = string;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string StrSplit(const std::string &inputStr, const std::string &delimiter, int num) {
    size_t start = 0, end = 0, count = 0;
    while ((end = inputStr.find(delimiter, start)) != std::string::npos) {
        if (++count == num) {
            return inputStr.substr(start, end - start);
        }
        start = end + delimiter.length();
    }
    if (count + 1 == num) {
        return inputStr.substr(start);
    }
    return "";
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}

int Mod(int dividend, int divisor) {
    return dividend % divisor;
}

// Function to check if the operating system is Windows
bool isWindows() {
    #ifdef _WIN32
        return true;
    #else
        return false;
    #endif
}

#ifdef _WIN32
    #define ARGC __argc
    #define ARGV __argv
#else
    extern char **environ;
    int ARGC;
    char** ARGV;
    __attribute__((constructor)) void init_args(int argc, char* argv[], char* envp[]) {
        ARGC = argc;
        ARGV = argv;
    }
#endif
std::string GetParams() {
    // [FIX] This function is now safe as it does not use std::filesystem.
    std::vector<std::string> params;
    for (int i = 1; i < ARGC; ++i) {
        params.push_back(ARGV[i]);
    }
    std::string result;
    for (const auto& param : params) {
        result += param + "\n";
    }
    return result;
}

std::string RegExReplace(std::string_view inputStr, std::string_view regexPattern, std::string_view replacement) {
#if USE_POWERFUL_REGEX
    // --- SRELL PATH ---
    try {
        const srell::regex re = srell::regex(regexPattern.data(), regexPattern.size());
        return srell::regex_replace(std::string(inputStr), re, std::string(replacement));
    } catch (const srell::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
        return std::string(inputStr); // Return original string on failure
    }
#else
    // --- FALLBACK PATH ---
    try {
        const std::regex re{std::string(regexPattern)};
        return std::regex_replace(std::string(inputStr), re, std::string(replacement));
    } catch (const std::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
        return std::string(inputStr); // Return original string on failure
    }
#endif
}

int RegExMatch(std::string_view haystack, std::string_view needle) {
#if USE_POWERFUL_REGEX
    // --- SRELL PATH ---
    try {
        const srell::regex re = srell::regex(needle.data(), needle.size());
        srell::cmatch match;
        if (srell::regex_search(haystack.data(), haystack.data() + haystack.size(), match, re)) {
            return match.position(0) + 1;
        }
    } catch (const srell::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
    }
#else
    // --- FALLBACK PATH ---
    try {
        const std::regex re{std::string(needle)};
        std::match_results<std::string_view::const_iterator> match;
        if (std::regex_search(haystack.begin(), haystack.end(), match, re)) {
            return match.position(0) + 1;
        }
    } catch (const std::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
    }
#endif
    return 0; // Return 0 on failure
}

void HTVM_Append(std::vector<std::string>& arr, const std::string& value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<std::string>& arr, const char* value) {
    arr.push_back(std::string(value));
}
void HTVM_Append(std::vector<int>& arr, int value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<float>& arr, float value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<bool>& arr, bool value) {
    arr.push_back(value);
}

void HTVM_Pop(std::vector<std::string>& arr) {
    if (!arr.empty()) arr.pop_back();
}
void HTVM_Pop(std::vector<int>& arr) {
    if (!arr.empty()) arr.pop_back();
}
void HTVM_Pop(std::vector<float>& arr) {
    if (!arr.empty()) arr.pop_back();
}
void HTVM_Pop(std::vector<bool>& arr) {
    if (!arr.empty()) arr.pop_back();
}

size_t HTVM_Size(const std::vector<std::string>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<int>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<float>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<bool>& arr) {
    return arr.size();
}


// HT-Bash
// Licensed under the GNU General Public License v3 (GPL v3)
// Copyright (c) 2026 TheMaster1127 aka Mr. Compiler
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//
// start of HT-Lib.htvm
// global vars NEEDED
int HT_LIB_theIdNumOfThe34 = 0;
std::vector<std::string> HT_Lib_theIdNumOfThe34theVar;
//;;;;;;;;;;;;;;;;;;;;;;;;;
std::string preserveStrings(std::string code, std::string keyWordEscpaeChar = "\\") {
    HT_LIB_theIdNumOfThe34 = 0;
    HT_Lib_theIdNumOfThe34theVar = {};
    std::vector<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
    std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    std::string str21 = "";
    std::string htCodeOUT754754 = "";
    std::string OutFixDoubleQuotesInsideDoubleQuotes = "";
    int fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
    int removeNexFixkeyWordEscpaeChar = 0;
    int areWEinSome34sNum = 0;
    std::vector<std::string> items1 = LoopParseFunc(code);
    for (size_t A_Index1 = 0; A_Index1 < items1.size(); A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        HTVM_Append(HT_Lib_theIdNumOfThe34theVar, "");
        HTVM_Append(HT_Lib_theIdNumOfThe34theVar, "");
    }
    std::vector<std::string> items2 = LoopParseFunc(code);
    for (size_t A_Index2 = 0; A_Index2 < items2.size(); A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        HT_Lib_theIdNumOfThe34theVar[A_Index2] = HT_Lib_theIdNumOfThe34theVar[A_Index2] + Chr(34);
        HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, A_LoopField2);
    }
    HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, " ");
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuuhuuhtheidFor" + str21 + "--" + str21 + "asds" + str21 + "as--" + str21 + "theuhtuwaesphoutr" + Chr(34);
    std::vector<std::string> items3 = LoopParseFunc(code);
    for (size_t A_Index3 = 0; A_Index3 < items3.size(); A_Index3++) {
        std::string A_LoopField3 = items3[A_Index3 - 0];
        if (A_LoopField3 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index3 + 1] == Chr(34)) {
            fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
            OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
        } else {
            if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField3;
            } else {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
            }
        }
    }
    code = OutFixDoubleQuotesInsideDoubleQuotes;
    if (keyWordEscpaeChar != Chr(92)) {
        code = StrReplace(code, Chr(92), Chr(92) + Chr(92));
    }
    if (keyWordEscpaeChar == Chr(92)) {
        std::vector<std::string> items4 = LoopParseFunc(code);
        for (size_t A_Index4 = 0; A_Index4 < items4.size(); A_Index4++) {
            std::string A_LoopField4 = items4[A_Index4 - 0];
            if (A_LoopField4 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField4 != Chr(34)) {
                    if (A_LoopField4 == keyWordEscpaeChar) {
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + Chr(92);
                    } else {
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + A_LoopField4;
                    }
                } else {
                    HT_LIB_theIdNumOfThe34++;
                    htCodeOUT754754 += "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(HT_LIB_theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField4 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField4;
                }
                areWEinSome34sNum = 0;
            }
        }
    } else {
        std::vector<std::string> items5 = LoopParseFunc(code);
        for (size_t A_Index5 = 0; A_Index5 < items5.size(); A_Index5++) {
            std::string A_LoopField5 = items5[A_Index5 - 0];
            if (A_LoopField5 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField5 != Chr(34)) {
                    if (A_LoopField5 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index5 + 1]) {
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + keyWordEscpaeChar;
                        removeNexFixkeyWordEscpaeChar = 1;
                    }
                    else if (A_LoopField5 == keyWordEscpaeChar) {
                        if (removeNexFixkeyWordEscpaeChar != 1) {
                            HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + Chr(92);
                        } else {
                            removeNexFixkeyWordEscpaeChar = 0;
                        }
                    } else {
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + A_LoopField5;
                    }
                } else {
                    HT_LIB_theIdNumOfThe34++;
                    htCodeOUT754754 += "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(HT_LIB_theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField5 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField5;
                }
                areWEinSome34sNum = 0;
            }
        }
    }
    code = htCodeOUT754754;
    for (int A_Index6 = 0; A_Index6 < HT_LIB_theIdNumOfThe34; A_Index6++) {
        HT_Lib_theIdNumOfThe34theVar[A_Index6] = HT_Lib_theIdNumOfThe34theVar[A_Index6] + Chr(34);
    }
    HTVM_Append(HT_Lib_theIdNumOfThe34theVar, Chr(34));
    return code;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string restoreStrings(std::string codeOUT, std::string keyWordEscpaeChar = Chr(92)) {
    for (int A_Index7 = 0; A_Index7 < HT_LIB_theIdNumOfThe34; A_Index7++) {
        if (HT_LIB_theIdNumOfThe34 == A_Index7 + 1) {
            codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index7 + 1) + Chr(65) + Chr(65), StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index7 + 1], keyWordEscpaeChar, "\\") + Chr(34));
        } else {
            codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index7 + 1) + Chr(65) + Chr(65), StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index7 + 1], keyWordEscpaeChar, "\\"));
        }
    }
    return codeOUT;
}
std::string cleanUpFirst(std::string code) {
    code = StrReplace(code, Chr(13), "");
    std::string out = "";
    std::vector<std::string> items8 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index8 = 0; A_Index8 < items8.size(); A_Index8++) {
        std::string A_LoopField8 = items8[A_Index8 - 0];
        out += Trim(A_LoopField8) + Chr(10);
    }
    out = StringTrimRight(out, 1);
    return out;
}
std::string getLangParams(std::string binName, std::string langExtension, std::string extra = "") {
    std::string params = Trim(GetParams());
    if (params == "") {
        if (isWindows()) {
            print("Usage:" + Chr(10) + Trim(binName) + " your_file." + Trim(langExtension) + " " + Trim(extra));
        } else {
            print("Usage:" + Chr(10) + "./" + Trim(binName) + " your_file." + Trim(langExtension) + " " + Trim(extra));
        }
        return "";
    } else {
        // Loop through the parameters and return the VERY FIRST one.
        std::vector<std::string> items9 = LoopParseFunc(params, "\n", "\r");
        for (size_t A_Index9 = 0; A_Index9 < items9.size(); A_Index9++) {
            std::string A_LoopField9 = items9[A_Index9 - 0];
            std::string first_param = Trim(A_LoopField9);
            if (first_param != "") {
                return first_param;
            }
        }
        // If all lines were empty for some reason, return nothing.
        return "";
    }
    // This is now unreachable, but good practice to keep.
    return "MASSIVE ERROR";
}
void saveOutput(std::string outCode, std::string fileName) {
    FileDelete(Trim(fileName));
    FileAppend(Trim(outCode), Trim(fileName));
    print("Generation finished: " + Trim(fileName) + " generated.");
}
bool beginning(std::string line, std::string what) {
    if (SubStr(line, 1, StrLen(what)) == what) {
        return true;
    }
    return false;
}
std::string formatCurlyBracesForParsing(std::string code, std::string openBrace = "{", std::string closeBrace = "}") {
    code = StrReplace(code, openBrace, Chr(10) + "{" + Chr(10));
    code = StrReplace(code, closeBrace, Chr(10) + "}" + Chr(10));
    code = cleanUpFirst(code);
    return code;
}
std::string handleComments(std::string code, std::string commentKeyword = ";") {
    std::string str1 = "";
    std::vector<std::string> items10 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index10 = 0; A_Index10 < items10.size(); A_Index10++) {
        std::string A_LoopField10 = items10[A_Index10 - 0];
        str1 += StrSplit(A_LoopField10, commentKeyword, 1) + Chr(10);
    }
    code = StringTrimRight(str1, 1);
    return code;
}
// Define the function to check odd spaces at the beginning
std::string CheckOddLeadingSpaces(std::string string123) {
    // Initialize a variable to count the spaces
    int spaceCount = 0;
    // Loop through the string one character at a time
    std::vector<std::string> items11 = LoopParseFunc(string123);
    for (size_t A_Index11 = 0; A_Index11 < items11.size(); A_Index11++) {
        std::string A_LoopField11 = items11[A_Index11 - 0];
        // Check if the current character is a space
        if (A_LoopField11 == Chr(32)) {
            spaceCount++;
        } else {
            // When we hit a non-space character, break the loop
            break;
        }
    }
    // Return true if the number of spaces is odd, false otherwise
    std::string sdsfawasd = STR(Mod(spaceCount, 2) == 1);
    //MsgBox, % sdsfawasd
    return sdsfawasd;
}
std::string RepeatSpaces(int count) {
    std::string spaces = "";
    for (int A_Index12 = 0; A_Index12 < count; A_Index12++) {
        spaces += Chr(32);
    }
    return spaces;
}
// if you wanna convert to python, nim etc... indentation style we set modeCurlyBracesOn to 0
std::string indent_nested_curly_braces(std::string input_string, int modeCurlyBracesOn = 1) {
    int indent_size = 4;
    int current_indent = 0;
    std::string result = "";
    std::string trimmed_line = "";
    std::string resultOut = "";
    std::string culyOpenFix = "{";
    std::string culyCloseFix = "}";
    //MsgBox, % input_string
    std::vector<std::string> items13 = LoopParseFunc(input_string, "\n", "\r");
    for (size_t A_Index13 = 0; A_Index13 < items13.size(); A_Index13++) {
        std::string A_LoopField13 = items13[A_Index13 - 0];
        trimmed_line = Trim(A_LoopField13);
        if (trimmed_line == Chr(123)) {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
            current_indent = current_indent + indent_size;
        }
        else if (trimmed_line == Chr(125)) {
            current_indent = current_indent - indent_size;
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
        } else {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
        }
    }
    if (modeCurlyBracesOn == 0) {
        std::string resultOut = "";
        std::vector<std::string> items14 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index14 = 0; A_Index14 < items14.size(); A_Index14++) {
            std::string A_LoopField14 = items14[A_Index14 - 0];
            if (Trim(A_LoopField14) != "{" && Trim(A_LoopField14) != "}") {
                resultOut += A_LoopField14 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        std::vector<std::string> lookIntoFurture;
        std::vector<std::string> items15 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index15 = 0; A_Index15 < items15.size(); A_Index15++) {
            std::string A_LoopField15 = items15[A_Index15 - 0];
            HTVM_Append(lookIntoFurture, Trim(A_LoopField15));
        }
        HTVM_Append(lookIntoFurture, " ");
        std::string resultOut = "";
        int skipNext = 0;
        std::vector<std::string> items16 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index16 = 0; A_Index16 < items16.size(); A_Index16++) {
            std::string A_LoopField16 = items16[A_Index16 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index16 + 1]) == "{") {
                resultOut += A_LoopField16 + " " + culyOpenFix + Chr(10);
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField16 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
        std::vector<std::string> lookIntoFurture2;
        std::vector<std::string> items17 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index17 = 0; A_Index17 < items17.size(); A_Index17++) {
            std::string A_LoopField17 = items17[A_Index17 - 0];
            HTVM_Append(lookIntoFurture2, Trim(A_LoopField17));
        }
        HTVM_Append(lookIntoFurture2, " ");
        resultOut = "";
        skipNext = 0;
        std::string addSpacesAtTheBegginig = "";
        std::vector<std::string> items18 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index18 = 0; A_Index18 < items18.size(); A_Index18++) {
            std::string A_LoopField18 = items18[A_Index18 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(A_LoopField18) == "}" && Trim(lookIntoFurture2[A_Index18 + 1]) == "else {") {
                skipNext = 2;
                addSpacesAtTheBegginig = "";
                std::vector<std::string> items19 = LoopParseFunc(A_LoopField18);
                for (size_t A_Index19 = 0; A_Index19 < items19.size(); A_Index19++) {
                    std::string A_LoopField19 = items19[A_Index19 - 0];
                    if (A_LoopField19 == " ") {
                        if (A_LoopField19 != " ") {
                            break;
                        }
                        addSpacesAtTheBegginig += StrReplace(A_LoopField19, "}", culyCloseFix);
                    }
                }
                resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + Chr(10);
            }
            if (skipNext == 0) {
                resultOut += A_LoopField18 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    std::string ALoopField = "";
    std::vector<std::string> items20 = LoopParseFunc(result, "\n", "\r");
    for (size_t A_Index20 = 0; A_Index20 < items20.size(); A_Index20++) {
        std::string A_LoopField20 = items20[A_Index20 - 0];
        if (CheckOddLeadingSpaces(A_LoopField20) == "1") {
            ALoopField = StringTrimLeft(A_LoopField20, 1);
            resultOut += ALoopField + Chr(10);
        } else {
            resultOut += A_LoopField20 + Chr(10);
        }
    }
    result = StringTrimRight(resultOut, 1);
    // Return the result
    return result;
}
// end of HT-Lib.htvm
std::string getLastChars(std::string line, int count) {
    std::string out = "";
    std::string out_temp = "";
    int len = StrLen(line);
    for (int A_Index21 = 0; A_Index21 < count; A_Index21++) {
        len--;
        std::vector<std::string> items22 = LoopParseFunc(line);
        for (size_t A_Index22 = 0; A_Index22 < items22.size(); A_Index22++) {
            std::string A_LoopField22 = items22[A_Index22 - 0];
            if (A_Index22 == len) {
                out_temp = A_LoopField22;
            }
        }
        out = out_temp + out;
    }
    return out;
}
std::string restoreStrings_bash(std::string codeOUT, std::string keyWordEscpaeChar = Chr(92)) {
    for (int A_Index23 = 0; A_Index23 < HT_LIB_theIdNumOfThe34; A_Index23++) {
        if (HT_LIB_theIdNumOfThe34 == A_Index23 + 1) {
            if (InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\a") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\b") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\e") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\f") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\r") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\t") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\v") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\n")) {
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), "$" + StrReplace(StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], Chr(34), Chr(39)), "$", "\\$"), keyWordEscpaeChar, "\\") + Chr(39));
            } else {
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "$", "\\$"), keyWordEscpaeChar, "\\") + Chr(34));
            }
        } else {
            if (InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\a") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\b") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\e") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\f") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\r") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\t") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\v") || InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\n")) {
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), "$" + StrReplace(StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], Chr(34), Chr(39)), "$", "\\$"), keyWordEscpaeChar, "\\"));
            } else {
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "$", "\\$"), keyWordEscpaeChar, "\\"));
            }
        }
    }
    return codeOUT;
}
std::string transformBracesToHT_Bash(std::string code) {
    std::string out = "";
    std::vector<std::string> blockStack;
    int ifNestLevel = 0;
    int loopNestLevel = 0;
    std::vector<std::string> items24 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index24 = 0; A_Index24 < items24.size(); A_Index24++) {
        std::string A_LoopField24 = items24[A_Index24 - 0];
        std::string currentLine = A_LoopField24;
        std::string trimmedLine = StrLower(Trim(currentLine));
        if (SubStr(trimmedLine, 1, 5) == "func ") {
            HTVM_Append(blockStack, "func:0");
            out += currentLine + Chr(10);
            continue;
        }
        // ===================================================================
        // IF BLOCKS
        // ===================================================================
        if (SubStr(trimmedLine, 1, 3) == "if ") {
            ifNestLevel++;
            HTVM_Append(blockStack, "if:" + STR(ifNestLevel));
            std::string newIfKeyword = "if";
            std::string conditionPart = SubStr(Trim(currentLine), 3);
            std::string modifiedIfLine = newIfKeyword + " " + conditionPart;
            int indentLen = InStr(StrLower(currentLine), "if") - 1;
            std::string indentation = SubStr(currentLine, 1, indentLen);
            out += indentation + modifiedIfLine + Chr(10);
            continue;
        }
        // ===================================================================
        // LOOP BLOCKS
        // ===================================================================
        if (SubStr(trimmedLine, 1, 5) == "loop,") {
            loopNestLevel++;
            HTVM_Append(blockStack, "loop:" + STR(loopNestLevel));
            std::string newLoopKeyword = "loop";
            std::string loopParams = SubStr(Trim(currentLine), 6);
            std::string modifiedLoopLine = newLoopKeyword + ", " + Trim(loopParams);
            int indentLen = InStr(StrLower(currentLine), "loop,") - 1;
            std::string indentation = SubStr(currentLine, 1, indentLen);
            out += indentation + modifiedLoopLine + Chr(10);
            continue;
        }
        if (SubStr(trimmedLine, 1, 6) == "while ") {
            loopNestLevel++;
            HTVM_Append(blockStack, "while:" + STR(loopNestLevel));
            std::string newLoopKeyword = "while";
            std::string loopParams = SubStr(Trim(currentLine), 6);
            std::string modifiedLoopLine = newLoopKeyword + " " + loopParams;
            int indentLen = InStr(StrLower(currentLine), "while") - 1;
            std::string indentation = SubStr(currentLine, 1, indentLen);
            out += indentation + modifiedLoopLine + Chr(10);
            continue;
        }
        if (SubStr(trimmedLine, 1, 12) == "loop, parse,") {
            loopNestLevel++;
            HTVM_Append(blockStack, "loopp:" + STR(loopNestLevel));
            std::string newLoopKeyword = "loop, parse,";
            std::string loopParams = SubStr(Trim(currentLine), 12);
            std::string modifiedLoopLine = newLoopKeyword + " " + loopParams;
            int indentLen = InStr(StrLower(currentLine), "loop, parse,") - 1;
            std::string indentation = SubStr(currentLine, 1, indentLen);
            out += indentation + modifiedLoopLine + Chr(10);
            continue;
        }
        if (trimmedLine == "loop") {
            loopNestLevel++;
            HTVM_Append(blockStack, "loopi:" + STR(loopNestLevel));
            std::string newLoopKeyword = "loop";
            std::string loopParams = SubStr(Trim(currentLine), 4);
            std::string modifiedLoopLine = newLoopKeyword + "," + loopParams;
            int indentLen = InStr(StrLower(currentLine), "loop") - 1;
            std::string indentation = SubStr(currentLine, 1, indentLen);
            out += indentation + "loop" + Chr(10);
            continue;
        }
        // ===================================================================
        // BRACES HANDLING
        // ===================================================================
        if (trimmedLine == "{") {
            continue;
        }
        if (trimmedLine == "}") {
            if (HTVM_Size(blockStack) == 0) {
                out += "SYNTAX ERROR: Unmatched closing brace found in HT-Bash." + Chr(10);
                continue;
            }
            std::string blockInfo = blockStack[HTVM_Size(blockStack) - 1];
            HTVM_Pop(blockStack);
            std::string blockType = StrSplit(blockInfo, ":", 1);
            int level = INT(StrSplit(blockInfo, ":", 2));
            int indentLen = InStr(currentLine, "}") - 1;
            std::string indentation = SubStr(currentLine, 1, indentLen);
            if (blockType == "func") {
                out += indentation + "funcend" + Chr(10);
            }
            else if (blockType == "if") {
                std::string ender = "fi";
                out += indentation + ender + Chr(10);
                ifNestLevel--;
            }
            else if (blockType == "loop") {
                std::string ender = "done";
                out += indentation + ender + Chr(10);
                loopNestLevel--;
            }
            else if (blockType == "loopi") {
                std::string ender = "done";
                out += indentation + ender + Chr(10);
                loopNestLevel--;
            }
            else if (blockType == "while") {
                std::string ender = "done2";
                out += indentation + ender + Chr(10);
                loopNestLevel--;
            }
            else if (blockType == "loopp") {
                std::string ender = "pdone";
                out += indentation + ender + Chr(10);
                loopNestLevel--;
            }
            continue;
        }
        out += currentLine + Chr(10);
    }
    if (HTVM_Size(blockStack) > 0) {
        out += "SYNTAX ERROR: " + STR(HTVM_Size(blockStack)) + " unclosed blocks at end of file in HT-Bash." + Chr(10);
    }
    return Trim(out);
}
std::string expressionTranspiler_2(std::string line, int mode = 0) {
    std::string out = "";
    int isConcat = 0;
    int isFirstTimeMath = 0;
    int isFirstTimeMath2 = 0;
    std::vector<std::string> items25 = LoopParseFunc(line, " ");
    for (size_t A_Index25 = 0; A_Index25 < items25.size(); A_Index25++) {
        std::string A_LoopField25 = items25[A_Index25 - 0];
        if (A_LoopField25 == ".") {
            isConcat = 1;
            break;
        }
    }
    if (isConcat == 1) {
        std::vector<std::string> items26 = LoopParseFunc(line, " ");
        for (size_t A_Index26 = 0; A_Index26 < items26.size(); A_Index26++) {
            std::string A_LoopField26 = items26[A_Index26 - 0];
            if (RegExMatch(A_LoopField26, "^-?\\d+(\\.\\d+)?$")) {
                out += Chr(34) + A_LoopField26 + Chr(34) + " ";
            }
            else if (InStr(A_LoopField26, "GUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFCAA")) {
                out += A_LoopField26 + " ";
            }
            else if (RegExMatch(A_LoopField26, "^[a-zA-Z_][a-zA-Z0-9_]*$")) {
                out += Chr(34) + "$" + A_LoopField26 + Chr(34) + " ";
            } else {
                out += A_LoopField26 + " ";
            }
        }
        line = Trim(out);
        out = "";
        std::vector<std::string> items27 = LoopParseFunc(line, " ");
        for (size_t A_Index27 = 0; A_Index27 < items27.size(); A_Index27++) {
            std::string A_LoopField27 = items27[A_Index27 - 0];
            if (A_LoopField27 == ".") {
                out += "";
            } else {
                out += A_LoopField27;
            }
        }
    } else {
        if (InStr(line, " + ") || InStr(line, " - ") || InStr(line, " * ") || InStr(line, " / ") || InStr(line, " ** ") || InStr(line, " % ") || RegExMatch(line, "^-?\\d+(\\.\\d+)?$")) {
            isFirstTimeMath = 1;
            if (mode == 0) {
                out += "$((";
            }
            std::vector<std::string> items28 = LoopParseFunc(line, " ");
            for (size_t A_Index28 = 0; A_Index28 < items28.size(); A_Index28++) {
                std::string A_LoopField28 = items28[A_Index28 - 0];
                out += A_LoopField28;
            }
            if (mode == 0) {
                out += "))";
            }
        } else {
            std::vector<std::string> items29 = LoopParseFunc(line, " ");
            for (size_t A_Index29 = 0; A_Index29 < items29.size(); A_Index29++) {
                std::string A_LoopField29 = items29[A_Index29 - 0];
                if (RegExMatch(A_LoopField29, "^-?\\d+(\\.\\d+)?$")) {
                    out += A_LoopField29 + " ";
                }
                else if (InStr(A_LoopField29, "GUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFCAA")) {
                    out += A_LoopField29 + " ";
                }
                else if (RegExMatch(A_LoopField29, "^[a-zA-Z_][a-zA-Z0-9_]*$")) {
                    out += Chr(34) + "$" + A_LoopField29 + Chr(34) + " ";
                } else {
                    out += A_LoopField29 + " ";
                }
            }
            line = Trim(out);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    return Trim(out);
}
std::string expressionTranspiler(std::string line, int mode = 0) {
    std::string out = "";
    std::string temp = "";
    if (InStr(line, ".size(") == false && InStr(line, ".add(") == false && InStr(line, ".pop(") == false) {
        line = Trim(StrReplace(line, "(", " ( "));
        line = Trim(StrReplace(line, ")", " ) "));
        if (RegExMatch(line, "(^|[^.])\\b([a-zA-Z_]\\w*)\\s*\\(")) {
            line = Trim(StrReplace(line, ",", " "));
            line = Trim(StrReplace(line, "  ", " "));
            line = Trim(StrReplace(line, "(", " "));
            line = Trim(StrReplace(line, ")", ""));
            std::vector<std::string> items30 = LoopParseFunc(line, " ");
            for (size_t A_Index30 = 0; A_Index30 < items30.size(); A_Index30++) {
                std::string A_LoopField30 = items30[A_Index30 - 0];
                temp = Trim(A_LoopField30);
                if (A_Index30 == 0) {
                    out += "$(" + A_LoopField30 + " ";
                } else {
                    if (InStr(temp, "[@]")) {
                        out += StringTrimRight(temp, 3) + " ";
                    } else {
                        out += expressionTranspiler_2(A_LoopField30, mode) + " ";
                    }
                }
            }
            out = Trim(out) + ")";
        } else {
            out = expressionTranspiler_2(line, mode);
        }
    } else {
        out = Trim(line);
    }
    out = RegExReplace(out, "([a-zA-Z0-9_]+)\\[(.*?)\\]", Chr(34) + "${$1[$2]}" + Chr(34));
    out = RegExReplace(out, "([a-zA-Z0-9_]+)\\.size\\(\\)", "${#$1[@]}");
    return Trim(out);
}
int main(int argc, char* argv[]) {
    std::string code = "";
    std::string out = "";
    std::string str1 = "";
    std::string str2 = "";
    std::string str3 = "";
    std::string str4 = "";
    std::string str5 = "";
    std::string str6 = "";
    std::string str7 = "";
    std::string str8 = "";
    std::string str9 = "";
    int whereBeginFuncOptanalParams = 0;
    int whereBeginFuncOptanalParams_help = 0;
    int whereBeginFuncOptanalParams_help_once = 0;
    std::string outTemp1 = "";
    std::string outTemp2 = "";
    std::string outTemp3 = "";
    std::string outTemp4 = "";
    int count = 0;
    int mathMode = 0;
    int firstLoop = 0;
    int firstLoop_parse = 0;
    int firstLoop_func = 0;
    int firstLoop_parse_func = 0;
    int inFunc = 0;
    std::string fix_curly_else_if = "";
    std::vector<std::string> fix_curly_else_if_ARR;
    std::vector<std::string> fixCode_runARR;
    std::string fixCode_run = "";
    int fixCode_run_INT = 0;
    std::string params = getLangParams("HT-Bash", "htsh");
    if (params != "") {
        code = FileRead(params);
        std::vector<std::string> items31 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index31 = 0; A_Index31 < items31.size(); A_Index31++) {
            std::string A_LoopField31 = items31[A_Index31 - 0];
            if (SubStr(StrLower(Trim(A_LoopField31)), 1, 4) == "run ") {
                str1 = Trim(StringTrimLeft(Trim(A_LoopField31), 4));
                HTVM_Append(fixCode_runARR, str1);
                fixCode_run += "run ht-bash_runrsfdhgiosdxxszpxx--ashdzxkcxwaSsdx--AA" + STR(fixCode_run_INT) + "AA" + Chr(10);
                fixCode_run_INT++;
            } else {
                fixCode_run += A_LoopField31 + Chr(10);
            }
        }
        code = Trim(fixCode_run);
        code = cleanUpFirst(code);
        code = preserveStrings(code);
        code = handleComments(code, ";");
        code = formatCurlyBracesForParsing(code);
        // code
        if (InStr(code, "{")) {
            fix_curly_else_if = "";
            std::vector<std::string> items32 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index32 = 0; A_Index32 < items32.size(); A_Index32++) {
                std::string A_LoopField32 = items32[A_Index32 - 0];
                HTVM_Append(fix_curly_else_if_ARR, A_LoopField32);
            }
            HTVM_Append(fix_curly_else_if_ARR, " ");
            std::vector<std::string> items33 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index33 = 0; A_Index33 < items33.size(); A_Index33++) {
                std::string A_LoopField33 = items33[A_Index33 - 0];
                if (Trim(A_LoopField33) == "}" && SubStr(Trim(StrLower(fix_curly_else_if_ARR[A_Index33 + 1])), 1, 8) == "else if ") {
                    fix_curly_else_if += "";
                }
                else if (Trim(A_LoopField33) == "{" && SubStr(Trim(StrLower(fix_curly_else_if_ARR[A_Index33 - 1])), 1, 8) == "else if ") {
                    fix_curly_else_if += "";
                }
                else if (Trim(A_LoopField33) == "}" && Trim(StrLower(fix_curly_else_if_ARR[A_Index33 + 1])) == "else") {
                    fix_curly_else_if += "";
                }
                else if (Trim(A_LoopField33) == "{" && Trim(StrLower(fix_curly_else_if_ARR[A_Index33 - 1])) == "else") {
                    fix_curly_else_if += "";
                } else {
                    fix_curly_else_if += A_LoopField33 + Chr(10);
                }
            }
            code = Trim(fix_curly_else_if);
            code = transformBracesToHT_Bash(code);
        }
        std::vector<std::string> items34 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index34 = 0; A_Index34 < items34.size(); A_Index34++) {
            std::string A_LoopField34 = items34[A_Index34 - 0];
            if (SubStr(StrLower(Trim(A_LoopField34)), 1, 4) == "run ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 4));
                out += str1 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 5) == "func ") {
                firstLoop_func = 0;
                firstLoop_parse_func = 0;
                inFunc = 1;
                str1 = "";
                str2 = "";
                str3 = "";
                str4 = "";
                str5 = "";
                str6 = "";
                str7 = "";
                str8 = "";
                str9 = "";
                whereBeginFuncOptanalParams = 0;
                whereBeginFuncOptanalParams_help = 0;
                whereBeginFuncOptanalParams_help_once = 0;
                str1 = Trim(StringTrimLeft(A_LoopField34, 5));
                str1 = Trim(StringTrimRight(str1, 1));
                str2 = Trim(StrSplit(str1, "(", 1));
                str3 = Trim(StrSplit(str1, "(", 2));
                out += str2 + "() {" + Chr(10);
                str4 = "";
                if (str3 != "") {
                    str4 = "";
                    str6 = "";
                    str7 = "";
                    whereBeginFuncOptanalParams = 0;
                    std::vector<std::string> items35 = LoopParseFunc(str3, ",");
                    for (size_t A_Index35 = 0; A_Index35 < items35.size(); A_Index35++) {
                        std::string A_LoopField35 = items35[A_Index35 - 0];
                        str5 = "";
                        if (InStr(A_LoopField35, " := ")) {
                            whereBeginFuncOptanalParams_help_once++;
                            if (whereBeginFuncOptanalParams_help_once == 1) {
                                whereBeginFuncOptanalParams = A_Index35 + 1;
                            }
                            str5 = Trim(StrSplit(A_LoopField35, " := ", 1));
                            str7 += Trim(StrSplit(A_LoopField35, " := ", 1)) + Chr(10);
                            str6 += expressionTranspiler(Trim(StrSplit(A_LoopField35, " := ", 2))) + Chr(10);
                            if (InStr(str5, "[@]")) {
                                str5 = Trim(str5);
                                str5 = StringTrimRight(str5, 3);
                                str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10);
                            }
                            else if (InStr(str5, "[]")) {
                                str5 = Trim(str5);
                                str5 = StringTrimRight(str5, 2);
                                str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10);
                            } else {
                                str4 += "local " + Trim(str5) + "=" + Chr(34) + "$" + STR(A_Index35 + 1) + Chr(34) + Chr(10);
                            }
                        } else {
                            str5 = A_LoopField35;
                            if (InStr(str5, "[@]")) {
                                str5 = Trim(str5);
                                str5 = StringTrimRight(str5, 3);
                                str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10);
                            }
                            else if (InStr(str5, "[]")) {
                                str5 = Trim(str5);
                                str5 = StringTrimRight(str5, 2);
                                str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10);
                            } else {
                                str4 += "local " + Trim(str5) + "=" + Chr(34) + "$" + STR(A_Index35 + 1) + Chr(34) + Chr(10);
                            }
                        }
                    }
                }
                out += Trim(str4) + Chr(10);
                if (str6 != "") {
                    str8 = "";
                    whereBeginFuncOptanalParams_help = 0;
                    std::vector<std::string> items36 = LoopParseFunc(str6, "\n", "\r");
                    for (size_t A_Index36 = 0; A_Index36 < items36.size(); A_Index36++) {
                        std::string A_LoopField36 = items36[A_Index36 - 0];
                        whereBeginFuncOptanalParams_help = A_Index36;
                        std::vector<std::string> items37 = LoopParseFunc(str7, "\n", "\r");
                        for (size_t A_Index37 = 0; A_Index37 < items37.size(); A_Index37++) {
                            std::string A_LoopField37 = items37[A_Index37 - 0];
                            if (A_Index37 == whereBeginFuncOptanalParams_help) {
                                str8 = A_LoopField37;
                                break;
                            }
                        }
                        out += "[ " + Chr(34) + "$#" + Chr(34) + " -lt " + STR(whereBeginFuncOptanalParams) + " ] && " + Trim(str8) + "=" + Trim(A_LoopField36) + Chr(10);
                        whereBeginFuncOptanalParams++;
                    }
                }
            }
            else if (Trim(StrLower(A_LoopField34)) == "funcend" || Trim(StrLower(A_LoopField34)) == "endfunc") {
                out += "}" + Chr(10);
                inFunc = 0;
            }
            else if (Trim(StrLower(A_LoopField34)) == "return") {
                out += "echo" + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 7) == "return ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 7));
                out += "echo " + expressionTranspiler(str1) + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 11) == "return_arr ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 11));
                out += "printf " + Chr(34) + "%s\\n" + Chr(34) + " " + expressionTranspiler(str1) + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 6) == "print(") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 6));
                str1 = Trim(StringTrimRight(str1, 1));
                if (InStr(str1, "GUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFCAA")) {
                    out += "printf " + Chr(34) + "%s\\n" + Chr(34) + " " + Trim(str1) + " >&2" + Chr(10);
                } else {
                    out += "printf " + Chr(34) + "%s\\n" + Chr(34) + " " + expressionTranspiler(str1) + " >&2" + Chr(10);
                }
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 10) == "local arr ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 10));
                str2 = Trim(StrSplit(str1, " := ", 1));
                str3 = Trim(StrSplit(str1, " := ", 2));
                if (InStr(str1, " := ")) {
                    str3 = StrReplace(str3, "[", "");
                    str3 = StrReplace(str3, "]", "");
                    str4 = "";
                    if (InStr(str3, ",")) {
                        std::vector<std::string> items38 = LoopParseFunc(str3, ",");
                        for (size_t A_Index38 = 0; A_Index38 < items38.size(); A_Index38++) {
                            std::string A_LoopField38 = items38[A_Index38 - 0];
                            str4 += expressionTranspiler(A_LoopField38) + " ";
                        }
                        str3 = Trim(str4);
                    }
                    out += "local " + str2 + "=(" + str3 + ")" + Chr(10);
                } else {
                    out += "local " + str2 + "=(" + expressionTranspiler(str3) + ")" + Chr(10);
                }
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 10) == "local str " || SubStr(StrLower(A_LoopField34), 1, 10) == "local int " || SubStr(StrLower(A_LoopField34), 1, 10) == "local var ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 10));
                str2 = Trim(StrSplit(str1, " := ", 1));
                str3 = Trim(StrSplit(str1, " := ", 2));
                out += "local " + str2 + "=" + expressionTranspiler(str3) + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 6) == "local " && InStr(A_LoopField34, " := ")) {
                str1 = Trim(StringTrimLeft(A_LoopField34, 6));
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " := ", 1));
                str3 = Trim(StrSplit(str1, " := ", 2));
                out += str2 + "=" + expressionTranspiler(str3) + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 4) == "str " || SubStr(StrLower(A_LoopField34), 1, 4) == "int " || SubStr(StrLower(A_LoopField34), 1, 4) == "var ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 4));
                str2 = Trim(StrSplit(str1, " := ", 1));
                str3 = Trim(StrSplit(str1, " := ", 2));
                out += str2 + "=" + expressionTranspiler(str3) + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 4) == "arr ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 4));
                str2 = Trim(StrSplit(str1, " := ", 1));
                str3 = Trim(StrSplit(str1, " := ", 2));
                if (InStr(str1, " := ")) {
                    str3 = StrReplace(str3, "[", "");
                    str3 = StrReplace(str3, "]", "");
                    str4 = "";
                    if (InStr(str3, ",")) {
                        std::vector<std::string> items39 = LoopParseFunc(str3, ",");
                        for (size_t A_Index39 = 0; A_Index39 < items39.size(); A_Index39++) {
                            std::string A_LoopField39 = items39[A_Index39 - 0];
                            str4 += expressionTranspiler(A_LoopField39) + " ";
                        }
                        str3 = Trim(str4);
                    }
                    out += str2 + "=(" + str3 + ")" + Chr(10);
                } else {
                    out += str2 + "=(" + expressionTranspiler(str3) + ")" + Chr(10);
                }
            }
            else if (InStr(A_LoopField34, " := []")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " := ", 1));
                out += str2 + "=()" + Chr(10);
            }
            else if (InStr(A_LoopField34, ".add(")) {
                str1 = Trim(A_LoopField34);
                str1 = Trim(StringTrimRight(str1, 1));
                str2 = Trim(StrSplit(str1, ".add(", 1));
                str3 = Trim(StrSplit(str1, ".add(", 2));
                out += str2 + "+=(" + expressionTranspiler(str3) + ")" + Chr(10);
            }
            else if (InStr(A_LoopField34, ".pop()")) {
                str1 = Trim(A_LoopField34);
                str1 = Trim(StringTrimRight(str1, 1));
                str2 = Trim(StrSplit(str1, ".pop(", 1));
                out += str2 + "=(" + Chr(34) + "${" + str2 + "[@]:0:${#" + str2 + "[@]}-1}" + Chr(34) + ")" + Chr(10);
            }
            else if (InStr(A_LoopField34, " := ") && InStr(A_LoopField34, " [") && InStr(A_LoopField34, "]")) {
                str1 = Trim(A_LoopField34);
                if (InStr(str1, " := ")) {
                    str2 = Trim(StrSplit(str1, " := ", 1));
                    str3 = Trim(StrSplit(str1, " := ", 2));
                    str3 = StrReplace(str3, "[", "");
                    str3 = StrReplace(str3, "]", "");
                    str4 = "";
                    if (InStr(str3, ",")) {
                        std::vector<std::string> items40 = LoopParseFunc(str3, ",");
                        for (size_t A_Index40 = 0; A_Index40 < items40.size(); A_Index40++) {
                            std::string A_LoopField40 = items40[A_Index40 - 0];
                            str4 += expressionTranspiler(A_LoopField40) + " ";
                        }
                        str3 = Trim(str4);
                    }
                    out += str2 + "=(" + str3 + ")" + Chr(10);
                } else {
                    out += str2 + "=(" + expressionTranspiler(str3) + ")" + Chr(10);
                }
            }
            else if (InStr(A_LoopField34, " := @")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " := @", 1));
                str3 = Trim(StrSplit(str1, " := @", 2));
                str3 = Trim(expressionTranspiler(str3));
                str3 = Trim(StringTrimLeft(str3, 1));
                out += "mapfile -t " + str2 + " < <" + str3 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 13) == "loop, parse, ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 13));
                if (inFunc == 0) {
                    firstLoop++;
                    firstLoop_parse++;
                    if (firstLoop == 1) {
                        out += "A_Index_stack=()" + Chr(10);
                        out += "A_Index=0" + Chr(10);
                    }
                    if (firstLoop_parse == 1) {
                        out += "A_LoopField_stack=()" + Chr(10);
                        out += "A_LoopField=" + Chr(34) + Chr(34) + Chr(10);
                    }
                    out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10);
                    out += "A_LoopField_stack+=(" + Chr(34) + "$A_LoopField" + Chr(34) + ")" + Chr(10);
                    if (InStr(str1, ",")) {
                        str2 = Trim(StrSplit(str1, ",", 1));
                        str3 = Trim(StrSplit(str1, ",", 2));
                        str4 = Chr(10);
                        str4 += "_parse_str=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10);
                        str4 += "_parse_delim=" + str3 + Chr(10);
                        str4 += "_temp_arr_" + STR(firstLoop_parse) + "=(); IFS=" + Chr(34) + "$_parse_delim" + Chr(34) + " read -r -d '' -a _temp_arr_" + STR(firstLoop_parse) + " <<< " + Chr(34) + "$_parse_str" + Chr(34) + "; _temp_arr_" + STR(firstLoop_parse) + "[-1]=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse) + "[-1]%$'\\n'}" + Chr(34) + Chr(10);
                        str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse) + "[@]}; A_Index++)); do" + Chr(10);
                        str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse) + "[$A_Index]}" + Chr(34) + Chr(10);
                    } else {
                        //;;;;;;;;;;;;;
                        //;;;;;;;;;;;;;
                        str2 = Trim(str1);
                        str4 = Chr(10);
                        str4 += "_temp_arr_" + STR(firstLoop_parse) + "=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10);
                        str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse) + "}; A_Index++)); do" + Chr(10);
                        str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse) + ":A_Index:1}" + Chr(34) + Chr(10);
                        //;;;;;;;;;;;;;
                        //;;;;;;;;;;;;;
                    }
                    out += str4 + Chr(10);
                } else {
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    firstLoop_func++;
                    firstLoop_parse_func++;
                    if (firstLoop_func == 1) {
                        out += "local A_Index_stack=()" + Chr(10);
                        out += "local A_Index=0" + Chr(10);
                    }
                    if (firstLoop_parse_func == 1) {
                        out += "local A_LoopField_stack=()" + Chr(10);
                        out += "local A_LoopField=" + Chr(34) + Chr(34) + Chr(10);
                    }
                    out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10);
                    out += "A_LoopField_stack+=(" + Chr(34) + "$A_LoopField" + Chr(34) + ")" + Chr(10);
                    if (InStr(str1, ",")) {
                        str2 = Trim(StrSplit(str1, ",", 1));
                        str3 = Trim(StrSplit(str1, ",", 2));
                        str4 = Chr(10);
                        str4 += "local _parse_str=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10);
                        str4 += "local _parse_delim=" + str3 + Chr(10);
                        str4 += "local -a _temp_arr_" + STR(firstLoop_parse_func) + "; IFS=" + Chr(34) + "$_parse_delim" + Chr(34) + " read -r -d '' -a _temp_arr_" + STR(firstLoop_parse_func) + " <<< " + Chr(34) + "$_parse_str" + Chr(34) + "; _temp_arr_" + STR(firstLoop_parse_func) + "[-1]=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse_func) + "[-1]%$'\\n'}" + Chr(34) + Chr(10);
                        str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse_func) + "[@]}; A_Index++)); do" + Chr(10);
                        str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse_func) + "[$A_Index]}" + Chr(34) + Chr(10);
                    } else {
                        //;;;;;;;;;;;;;
                        //;;;;;;;;;;;;;
                        str2 = Trim(str1);
                        str4 = Chr(10);
                        str4 += "local _temp_arr_" + STR(firstLoop_parse_func) + "=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10);
                        str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse_func) + "}; A_Index++)); do" + Chr(10);
                        str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse_func) + ":A_Index:1}" + Chr(34) + Chr(10);
                        //;;;;;;;;;;;;;
                        //;;;;;;;;;;;;;
                    }
                    out += str4 + Chr(10);
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                }
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 6) == "loop, ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 6));
                if (inFunc == 0) {
                    firstLoop++;
                    if (firstLoop == 1) {
                        out += "A_Index_stack=()" + Chr(10);
                        out += "A_Index=0" + Chr(10);
                    }
                    out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10);
                    if (InStr(str1, ".size(")) {
                        out += "for ((A_Index=0; A_Index<" + expressionTranspiler(Trim(str1)) + "; A_Index++)); do" + Chr(10);
                    } else {
                        out += "for ((A_Index=0; A_Index<" + Trim(str1) + "; A_Index++)); do" + Chr(10);
                    }
                } else {
                    firstLoop_func++;
                    if (firstLoop_func == 1) {
                        out += "local A_Index_stack=()" + Chr(10);
                        out += "local A_Index=0" + Chr(10);
                    }
                    out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10);
                    if (InStr(str1, ".size(")) {
                        out += "for ((A_Index=0; A_Index<" + expressionTranspiler(Trim(str1)) + "; A_Index++)); do" + Chr(10);
                    } else {
                        out += "for ((A_Index=0; A_Index<" + Trim(str1) + "; A_Index++)); do" + Chr(10);
                    }
                }
            }
            else if (Trim(StrLower(A_LoopField34)) == "loop") {
                if (inFunc == 0) {
                    firstLoop++;
                    if (firstLoop == 1) {
                        out += "A_Index_stack=()" + Chr(10);
                        out += "A_Index=0" + Chr(10);
                    }
                    out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10);
                    out += "for ((A_Index=0;; A_Index++)); do" + Chr(10);
                } else {
                    firstLoop_func++;
                    if (firstLoop_func == 1) {
                        out += "local A_Index_stack=()" + Chr(10);
                        out += "local A_Index=0" + Chr(10);
                    }
                    out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10);
                    out += "for ((A_Index=0;; A_Index++)); do" + Chr(10);
                }
            }
            else if (Trim(A_LoopField34) == "done") {
                out += Trim(A_LoopField34) + Chr(10);
                out += "A_Index=" + Chr(34) + "${A_Index_stack[-1]}" + Chr(34) + Chr(10);
                out += "unset 'A_Index_stack[-1]'" + Chr(10);
            }
            else if (Trim(A_LoopField34) == "pdone") {
                out += "done" + Chr(10);
                out += "A_Index=" + Chr(34) + "${A_Index_stack[-1]}" + Chr(34) + Chr(10);
                out += "unset 'A_Index_stack[-1]'" + Chr(10);
                out += "A_LoopField=" + Chr(34) + "${A_LoopField_stack[-1]}" + Chr(34) + Chr(10);
                out += "unset 'A_LoopField_stack[-1]'" + Chr(10);
            }
            else if (Trim(A_LoopField34) == "break") {
                out += Trim(A_LoopField34) + Chr(10);
            }
            else if (Trim(A_LoopField34) == "continue") {
                out += Trim(A_LoopField34) + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 3) == "if " || SubStr(StrLower(A_LoopField34), 1, 8) == "else if ") {
                if (SubStr(StrLower(A_LoopField34), 1, 8) == "else if ") {
                    str1 = Trim(StringTrimLeft(A_LoopField34, 8));
                } else {
                    str1 = Trim(StringTrimLeft(A_LoopField34, 3));
                }
                mathMode = 0;
                if (getLastChars(Trim(A_LoopField34), 1) == ")") {
                    str1 = Trim(StringTrimLeft(str1, 1));
                    str1 = Trim(StringTrimRight(str1, 1));
                    mathMode = 1;
                }
                str2 = "";
                std::vector<std::string> items41 = LoopParseFunc(str1, " ");
                for (size_t A_Index41 = 0; A_Index41 < items41.size(); A_Index41++) {
                    std::string A_LoopField41 = items41[A_Index41 - 0];
                    if (RegExMatch(A_LoopField41, "^-?\\d+(\\.\\d+)?$")) {
                        str2 += A_LoopField41 + " ";
                        mathMode = 1;
                    }
                    else if (A_LoopField41 == ".") {
                        str2 += "";
                    }
                    else if (A_LoopField41 == "==") {
                        str2 += " == ";
                    }
                    else if (A_LoopField41 == "=") {
                        str2 += " == ";
                    }
                    else if (A_LoopField41 == ">") {
                        str2 += " > ";
                    }
                    else if (A_LoopField41 == "<") {
                        str2 += " < ";
                    }
                    else if (A_LoopField41 == ">=") {
                        str2 += " >= ";
                    }
                    else if (A_LoopField41 == "<=") {
                        str2 += " <= ";
                    }
                    else if (A_LoopField41 == "!=") {
                        str2 += " != ";
                    } else {
                        if (mathMode == 0) {
                            str2 += expressionTranspiler(A_LoopField41);
                        } else {
                            str2 += A_LoopField41 + " ";
                        }
                    }
                }
                if (SubStr(StrLower(A_LoopField34), 1, 8) == "else if ") {
                    if (mathMode == 0) {
                        out += "elif [[ " + str2 + " ]]; then" + Chr(10);
                    } else {
                        out += "elif (( " + str2 + " )); then" + Chr(10);
                    }
                } else {
                    if (mathMode == 0) {
                        out += "if [[ " + str2 + " ]]; then" + Chr(10);
                    } else {
                        out += "if (( " + str2 + " )); then" + Chr(10);
                    }
                }
            }
            else if (Trim(A_LoopField34) == "fi") {
                out += Trim(A_LoopField34) + Chr(10);
            }
            else if (Trim(A_LoopField34) == "else") {
                out += Trim(A_LoopField34) + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 6) == "while ") {
                str1 = Trim(StringTrimLeft(A_LoopField34, 6));
                mathMode = 0;
                if (getLastChars(Trim(A_LoopField34), 1) == ")") {
                    str1 = Trim(StringTrimLeft(str1, 1));
                    str1 = Trim(StringTrimRight(str1, 1));
                    mathMode = 1;
                }
                str2 = "";
                std::vector<std::string> items42 = LoopParseFunc(str1, " ");
                for (size_t A_Index42 = 0; A_Index42 < items42.size(); A_Index42++) {
                    std::string A_LoopField42 = items42[A_Index42 - 0];
                    if (RegExMatch(A_LoopField42, "^-?\\d+(\\.\\d+)?$")) {
                        str2 += A_LoopField42 + " ";
                        mathMode = 1;
                    }
                    else if (A_LoopField42 == ".") {
                        str2 += "";
                    }
                    else if (A_LoopField42 == "==") {
                        str2 += " == ";
                    }
                    else if (A_LoopField42 == "=") {
                        str2 += " == ";
                    }
                    else if (A_LoopField42 == ">") {
                        str2 += " > ";
                    }
                    else if (A_LoopField42 == "<") {
                        str2 += " < ";
                    }
                    else if (A_LoopField42 == ">=") {
                        str2 += " >= ";
                    }
                    else if (A_LoopField42 == "<=") {
                        str2 += " <= ";
                    }
                    else if (A_LoopField42 == "!=") {
                        str2 += " != ";
                    } else {
                        if (mathMode == 0) {
                            str2 += expressionTranspiler(A_LoopField42);
                        } else {
                            str2 += A_LoopField42 + " ";
                        }
                    }
                }
                if (mathMode == 0) {
                    out += "while [[ " + str2 + " ]]; do" + Chr(10);
                } else {
                    out += "while (( " + str2 + " )); do" + Chr(10);
                }
            }
            else if (Trim(A_LoopField34) == "done2") {
                out += "done" + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField34), 1, 6) == "local " && InStr(A_LoopField34, " := ")) {
                str1 = Trim(StringTrimLeft(A_LoopField34, 6));
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " := ", 1));
                str3 = Trim(StrSplit(str1, " := ", 2));
                out += "local " + str2 + "=" + expressionTranspiler(str3) + Chr(10);
            }
            else if (InStr(A_LoopField34, " := ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " := ", 1));
                str3 = Trim(StrSplit(str1, " := ", 2));
                out += str2 + "=" + expressionTranspiler(str3) + Chr(10);
            }
            else if (InStr(A_LoopField34, " += ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " += ", 1));
                str3 = Trim(StrSplit(str1, " += ", 2));
                out += "(( " + str2 + " += " + expressionTranspiler(str3, 1) + " ))" + Chr(10);
            }
            else if (InStr(A_LoopField34, " -= ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " -= ", 1));
                str3 = Trim(StrSplit(str1, " -= ", 2));
                out += "(( " + str2 + " -= " + expressionTranspiler(str3, 1) + " ))" + Chr(10);
            }
            else if (InStr(A_LoopField34, " *= ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " *= ", 1));
                str3 = Trim(StrSplit(str1, " *= ", 2));
                out += "(( " + str2 + " *= " + expressionTranspiler(str3, 1) + " ))" + Chr(10);
            }
            else if (InStr(A_LoopField34, " /= ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " /= ", 1));
                str3 = Trim(StrSplit(str1, " /= ", 2));
                out += "(( " + str2 + " /= " + expressionTranspiler(str3, 1) + " ))" + Chr(10);
            }
            else if (InStr(A_LoopField34, " %= ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " %= ", 1));
                str3 = Trim(StrSplit(str1, " %= ", 2));
                out += "(( " + str2 + " %= " + expressionTranspiler(str3, 1) + " ))" + Chr(10);
            }
            else if (InStr(A_LoopField34, " **= ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " **= ", 1));
                str3 = Trim(StrSplit(str1, " **= ", 2));
                out += "(( " + str2 + " = " + str2 + " ** " + expressionTranspiler(str3, 1) + " ))" + Chr(10);
            }
            else if (InStr(A_LoopField34, " .= ")) {
                str1 = Trim(A_LoopField34);
                str2 = Trim(StrSplit(str1, " .= ", 1));
                str3 = Trim(StrSplit(str1, " .= ", 2));
                out += str2 + "+=" + expressionTranspiler(str3) + Chr(10);
            }
            else if (getLastChars(Trim(A_LoopField34), 2) == "++") {
                str1 = Trim(A_LoopField34);
                str1 = StringTrimRight(str1, 2);
                out += "(( " + str1 + "++ ))" + Chr(10);
            }
            else if (getLastChars(Trim(A_LoopField34), 2) == "--") {
                str1 = Trim(A_LoopField34);
                str1 = StringTrimRight(str1, 2);
                out += "(( " + str1 + "-- ))" + Chr(10);
            }
            else if (getLastChars(Trim(A_LoopField34), 1) == ")") {
                str1 = Trim(A_LoopField34);
                str1 = expressionTranspiler(str1);
                str1 = StringTrimLeft(str1, 2);
                str1 = StringTrimRight(str1, 1);
                str1 = StrReplace(str1, Chr(34) + "(", " ");
                out += str1 + Chr(10);
            } else {
                // else we allow stuff e.g.: program param param param ... so we can allow anything else
                out += A_LoopField34 + Chr(10);
            }
        }
        code = StringTrimRight(out, 1);
        // end code
        code = restoreStrings_bash(code);
        code = StrReplace(code, Chr(34) + "$" + Chr(34), "");
        code = StrReplace(code, Chr(34) + "ihuiuuhuuhtheidFor-" + Chr(45) + "asdsas--theuhtuwaesphoutr" , "\\");
        for (int A_Index43 = 0; A_Index43 < HTVM_Size(fixCode_runARR); A_Index43++) {
            code = StrReplace(code, "ht-bash_runrsfdhgiosdxxszpxx--ashdzxkcxwaSsdx--AA" + STR(A_Index43) + "AA", fixCode_runARR[A_Index43]);
        }
        code = "#!/usr/bin/env bash" + Chr(10) + "if ((BASH_VERSINFO[0] < 4 || (BASH_VERSINFO[0] == 4 && BASH_VERSINFO[1] < 3))); then" + Chr(10) + "    echo " + Chr(34) + "Error: This script requires Bash 4.3+. Update bash." + Chr(34) + " >&2" + Chr(10) + "    exit 1" + Chr(10) + "fi" + Chr(10) + Chr(10) + "source " + Chr(34) + "$(dirname " + Chr(34) + "$0" + Chr(34) + ")/HT-Bash_Lib.sh" + Chr(34) + Chr(10) + code;
        saveOutput(code, StringTrimRight(params, 4) + "sh");
    }
    

    return 0;
}