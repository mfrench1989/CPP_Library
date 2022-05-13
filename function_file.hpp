#ifndef FUNCTIONFILE_HPP
#define FUNCTIONFILE_HPP

#include <string>
#include <vector>

#define FILE_ERROR -1
#define SECTION_END "#END"
#define SECTION_HEAD "#"
#define SECTION_END_OLD "}" //TODO: Old style sections, delete when possible
#define SECTION_START_OLD "{" //TODO: Old style sections, delete when possible

/**
 * @brief dirCreate - create directory and subdirectories specified by path
 * @param string - path to directory
 */
void dirCreate(const std::string&);

/**
 * @brief fileAppend - append string to end of file
 * @param string - path to file
 * @param string - string to append
 */
void fileAppend(const std::string&, const std::string&);

/**
 * @brief fileWrite - write vector to file path
 * @param string - path to file
 * @param vector<string> - vector of strings, each index is a line in the file
 */
void fileWrite(const std::string&, const std::vector<std::string>&);

/**
 * @brief fileCopy - copies file from one location to another
 * @param string - path to file
 * @param string - path to copy location
 * @return
 */
bool fileCopy(const std::string&, const std::string&);

/**
 * @brief fileDeleteAll - delete all files matching the pattern string
 * @return
 */
bool fileDelete(const std::string&, const std::string&);

/**
 * @brief fileExists - check if file exists
 * @return
 */
bool fileExists(const std::string&);

/**
 * @brief fileIndex - find index in nested sections that starts with the pattern string
 * @param vector<string> - file vector
 * @param vector<string> - nested section vector
 * @param string - pattern string
 * @return
 */
int fileIndexOf(const std::vector<std::string>&, const std::vector<std::string>&, const std::string&);

/**
 * @brief fileSectionEndOf - find the end of the section starting from current index
 * @param vector<string> - file vector
 * @param int - current index, should not be a section start
 * @return
 */
int fileSectionEndOf(const std::vector<std::string>&, int);

/**
 * @brief fileSectionHead - find the start of the nested section
 * @param vector<string> - file vector
 * @param vector<string> - nested section vector
 * @return
 */
int fileSectionHead(const std::vector<std::string>&, const std::vector<std::string>&);
/**
 * @brief fileSectionHeadOf - find the start of the section starting from current index
 * @param vector<string> - file vector
 * @param int - current index, should not be a section end
 * @return
 */
int fileSectionHeadOf(const std::vector<std::string>&, int);

/**
 * @brief fileValueOf - returns the value of pattern string
 * @param vector<string> - file vector
 * @param vector<string> - nested section vector
 * @param string - pattern string
 * @return
 */
std::string fileValueOf(const std::vector<std::string>&, const std::vector<std::string>&, const std::string&);

/**
 * @brief dirList - return a list of directories
 * @param string - directory path
 * @return
 */
std::vector<std::string> dirList(const std::string&);

/**
 * @brief fileClean - clean file of comments, white space characters, and empty lines
 * @param vector<string> - file vector to clean
 * @param bool - remove comments
 * @param bool - remove leading/trailing white spaces
 * @param bool - remove all white spaces
 * @param bool - remove empty lines
 * @return
 */
std::vector<std::string> fileClean(std::vector<std::string>, const bool, const bool, const bool);

/**
 * @brief fileFormat - format file with appropriate tabbing
 * @param vector<string> - file vector to format
 * @return
 */
std::vector<std::string> fileFormat(std::vector<std::string>);

/**
 * @brief fileSection - get all the lines of a nested section
 * @param vector<string> - file vector
 * @param vector<string> - nested section vector
 * @return
 */
std::vector<std::string> fileGetSection(const std::vector<std::string>&, const std::vector<std::string>&);

/**
 * @brief fileSection - get all the lines of a nested section
 * @param vector<string> - file vector
 * @param int - current index, should not be a section start
 * @return
 */
std::vector<std::string> fileGetSectionOf(const std::vector<std::string>&, int);

/**
 * @brief fileList - get a list of files with that match the pattern string
 * @param string - directory path
 * @param string - pattern string to match
 * @return
 */
std::vector<std::string> fileList(const std::string&, const std::string&);

/**
 * @brief fileListSection - get a list of sections within vector, will not show nested sections
 * @param vector<string> - file vector to get list of
 * @return
 */
std::vector<std::string> fileListSection(const std::vector<std::string>&);

/**
 * @brief fileRead - read file line by line into a vector of strings
 * @param string - path to file
 * @return
 */
std::vector<std::string> fileRead(const std::string&);

/**
 * @brief fileReplace - single pass, replace all instances of a substring within each string
 * @param std::vector<std::string> - vecter to iterate through and replace strings
 * @param string - string to find and replace
 * @param string - string to replace the found string with
 * @return
 */
std::vector<std::string> fileReplace(std::vector<std::string>, const std::string&, const std::string&);

/**
 * @brief fileReplaceSection - replace all lines in nested section
 * @param vector<string> - file vector
 * @param vector<string> - nested section vector
 * @param vector<string> - replace vector
 * @return
 */
std::vector<std::string> fileReplaceSection(std::vector<std::string>, const std::vector<std::string>&, const std::vector<std::string>&);

/**
 * @brief fileSort - sort file sections to alphabetical order, does not sort nested sections
 * @param vector<string> - file vector to sort
 * @return
 */
std::vector<std::string> fileSort(const std::vector<std::string>&);



//TODO: Old style sections, delete when possible
int fileIndexOf_OLD(const std::vector<std::string>&, const std::vector<std::string>&, const std::string&);
int fileSectionEndOf_OLD(const std::vector<std::string>&, int);
int fileSectionHead_OLD(const std::vector<std::string>&, const std::vector<std::string>&);
int fileSectionHeadOf_OLD(const std::vector<std::string>&, int);
std::string fileValueOf_OLD(const std::vector<std::string>&, const std::vector<std::string>&, const std::string&);
std::vector<std::string> fileFormat_OLD(std::vector<std::string>);
std::vector<std::string> fileGetSection_OLD(const std::vector<std::string>&, const std::vector<std::string>&);
std::vector<std::string> fileGetSectionOf_OLD(const std::vector<std::string>&, int);
std::vector<std::string> fileListSection_OLD(const std::vector<std::string>&);
std::vector<std::string> fileReplaceSection_OLD(std::vector<std::string>, const std::vector<std::string>&, const std::vector<std::string>&);
std::vector<std::string> fileSort_OLD(const std::vector<std::string>&);

//archive file? this should probably be a separate function set for including the 7 zip sdk stuff?

#endif // FUNCTIONFILE_HPP
