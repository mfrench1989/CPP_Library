#ifndef FUNCTIONSTRING_HPP
#define FUNCTIONSTRING_HPP

#include <string>
#include <vector>

#define DELIMITER_COMMENT "//"

/**
 * @brief stringIsAlphabetic - compare alphabetical order of strings
 * @param string - first string to compare
 * @param string - second string to compare
 * @return
 */
bool stringIsAlphabetic(const std::string&, const std::string&);

/**
 * @brief stringIsMatch - match string to pattern containing wildcards.
 * '*' matches 0 or more instances of any character(s).
 * '?' matches any one character
 * @param char* - pattern to match against
 * @param char* - string to compare
 * @param bool - case sensitive flag
 * @return
 */
bool stringIsMatch(const char*, const char*);

/**
 * @brief stringIsNum - check if string is a number
 * @param string - string to check
 * @return
 */
bool stringIsNum(const std::string&);

/**
 * @brief stringToChar - store string in character array passed as pointer
 * @param string - string to convert to char array
 * @param char - pointer to char array
 * @param int - size of char array
 * @return
 */
bool stringToChar(const std::string&, char*, const int);

/**
 * @brief stringToNum - convert string to number
 * @param string - string to convert
 * @return
 */
double stringToNum(const std::string&);

/**
 * @brief stringClean - remove comments and white spaces from a string
 * @param string - string to clean
 * @param bool - remove comments
 * @param bool - remove leading/trailing white spaces
 * @param bool - remove all white spaces
 * @return
 */
std::string stringClean(std::string, const bool, const bool, const bool);

/**
 * @brief stringColor - convert RGB values (0-255) to hex color
 * @param int - red color value
 * @param int - green color value
 * @param int - blue color value
 * @return
 */
std::string stringColor(const int, const int, const int);

/**
 * @brief stringGetComment - returns the comment portion of a string
 * @param string - string to find comment in
 * @return
 */
std::string stringComment(std::string);

/**
 * @brief stringDateTime - get current date/time formatted based on string passed
 * @param string - string of date-time format
 * @return
 */
std::string stringDateTime(const std::string&);

/**
 * @brief stringHTML - format string for HTML rich text
 * @param string - string to format
 * @param string - hex string for color
 * @param bool - bold text flag
 * @return
 */
std::string stringHTML(std::string, const std::string&, const bool);

/**
 * @brief stringJoin - join a vector of strings separated by a delimiter
 * @param vector<string> - vector of strings to join
 * @param string - delimiter string to insert between every index
 * @return
 */
std::string stringJoin(const std::vector<std::string>&, const std::string&);

/**
 * @brief stringReplace - single pass, replace all instances of a substring within a string
 * @param string - string to iterate through
 * @param string - string to find and replace
 * @param string - string to replace the found string with
 * @return
 */
std::string stringReplace(std::string, const std::string&, const std::string&);

/**
 * @brief stringToLower - convert the string to all lowercase characters
 * @param string - string to convert
 * @return
 */
std::string stringToLower(std::string);

/**
 * @brief stringToBytes - convert string to a vector of bytes
 * @param string - string to convert
 * @return
 */
std::vector<char> stringToBytes(const std::string&);

/**
 * @brief structToBytes - convert struct to a vector of bytes
 * @param void - pointer to struct to convert
 * @param int - size of struct to convert
 * @return
 */
std::vector<char> structToBytes(void*, const int);

/**
 * @brief stringSplit - split string at every instance of delimiter
 * @param string - string to split
 * @param string - string of delimiter to split along
 * @return
 */
std::vector<std::string> stringSplit(const std::string&, const std::string&);

#endif // FUNCTIONSTRING_HPP
