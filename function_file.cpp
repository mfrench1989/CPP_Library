#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "function_string.hpp"

#include "function_file.hpp"

void dirCreate(const std::string& dir_path) {
  /*Ensure dir_path is not an empty string*/
  if (!dir_path.empty()) {
      std::filesystem::create_directories(dir_path);
    }
}

void fileAppend(const std::string& file_path, const std::string& string_append) {
  /*Create directory if none exists*/
  std::vector<std::string> vector_dir = stringSplit(file_path, "/");
  vector_dir.pop_back();
  dirCreate(stringJoin(vector_dir, "/"));

  /*Open file for appending*/
  std::ofstream file_out(file_path, std::ios_base::app);
  file_out << string_append << std::endl;
  file_out.close();
}

void fileWrite(const std::string& file_path, const std::vector<std::string>& vector_file) {
  /*Create directory if none exists*/
  std::vector<std::string> vector_dir = stringSplit(file_path, "/");
  vector_dir.pop_back();
  dirCreate(stringJoin(vector_dir, "/"));

  /*Open file for overwriting*/
  std::ofstream file_out(file_path, std::ios_base::trunc);
  for (const std::string& string_line : vector_file) {
      file_out << string_line;

      /*Write new line character only if not the last line*/
      if (&string_line != &vector_file.back()) {
          file_out << std::endl;
        }
    }
  file_out.close();
}

bool fileCopy(const std::string& file_path, const std::string& copy_path) {
  std::vector<std::string> vector_copy = stringSplit(copy_path, "/");
  vector_copy.pop_back();
  dirCreate(stringJoin(vector_copy, "/"));

  return std::filesystem::copy_file(file_path, copy_path);
}

bool fileDeleteAll(const std::string& dir_path, const std::string& file_pattern) {
  bool remove_out = false;
  std::vector<std::string> vector_files = fileList(dir_path, std::string());
  for (const std::string& file : vector_files) {
      if (stringIsMatch(file_pattern.c_str(), file.c_str()) && std::filesystem::remove(dir_path + "/" + file)) {
          remove_out = true;
        }
    }
  return remove_out;
}

bool fileExists(const std::string& file_path) {
  return std::filesystem::exists(file_path);
}

int fileIndexOf(const std::vector<std::string>& vector_file, const std::vector<std::string>& vector_section, const std::string& index_pattern) {
  int index_current = 0;
  int index_end = vector_file.size();

  /*If nested sections update index_current and index_end*/
  if (!vector_section.empty()) {
      /*Get index_current and check if error*/
      if ((index_current = fileSectionHead(vector_file, vector_section)) == FILE_ERROR) {
          return FILE_ERROR;
        }
      /*Returned value is section start, move to first index of section*/
      ++index_current;

      /*Get index_end and check if error*/
      if ((index_end = fileSectionEndOf(vector_file, index_current)) == FILE_ERROR) {
          return FILE_ERROR;
        }
    }

  /*Iterate through vector_file attempting to find index_pattern*/
  for (; index_current < index_end; ++index_current) {
      /*Found index_pattern*/
      if (vector_file.at(index_current).find(index_pattern) == 0) {
          return index_current;
        }
      /*Clean file strings to ensure matches for section checks*/
      std::string string_file = stringClean(vector_file.at(index_current), true, true, false);
      /*Found section header, skip over section*/
      /*Get index_current and check if error*/
      if (string_file.find(SECTION_HEAD) == 0 && string_file != SECTION_END &&
          (index_current = fileSectionEndOf(vector_file, index_current + 1)) == FILE_ERROR) {
          return FILE_ERROR;
        }
    }
  return FILE_ERROR;
}

int fileSectionEndOf(const std::vector<std::string>& vector_file, int index_current) {
  /*Iterate through vector_file to find SECTION_END*/
  for (; index_current < static_cast<int>(vector_file.size()); ++index_current) {
      /*Clean file strings to ensure matches*/
      std::string string_file = stringClean(vector_file.at(index_current), true, true, false);
      /*Found SECTION_END*/
      if (string_file == SECTION_END) {
          return index_current;
        }
      /*Found section header, skip over section*/
      /*Get index_current and check if error*/
      if (string_file.find(SECTION_HEAD) == 0 && string_file != SECTION_END &&
          (index_current = fileSectionEndOf(vector_file, index_current + 1)) == FILE_ERROR) {
          return FILE_ERROR;
        }
    }
  return FILE_ERROR;
}

int fileSectionHead(const std::vector<std::string>& vector_file, const std::vector<std::string>& vector_section) {
  int index_current = 0;
  int index_end = vector_file.size();

  /*Iterate through vector_section to find start of last section*/
  for (const std::string& string_section : vector_section) {
      for (; index_current < index_end; ++index_current) {
          /*Clean file strings to ensure matches*/
          std::string string_file = stringClean(vector_file.at(index_current), true, true, false);
          /*Found section header*/
          if (string_file.find(SECTION_HEAD) == 0 && string_file != SECTION_END) {
              /*Section header is string_section*/
              if (string_file == std::string(SECTION_HEAD) + string_section) {
                  /*string_section is last section, return index*/
                  if (&string_section == &vector_section.back()) {
                      return index_current;
                    }
                  /*Increment index to avoid catching previous section header on next pass*/
                  ++index_current;
                  /*Get index_end and check if error*/
                  if ((index_end = fileSectionEndOf(vector_file, index_current)) == FILE_ERROR) {
                      return FILE_ERROR;
                    }
                  /*Break to go to next in vector_section*/
                  break;
                }
              /*Section header is NOT string_section, skip over section*/
              /*Get index_current and check if error*/
              if ((index_current = fileSectionEndOf(vector_file, index_current + 1)) == FILE_ERROR) {
                  return FILE_ERROR;
                }
            }
        }
    }
  return FILE_ERROR;
}

int fileSectionHeadOf(const std::vector<std::string>& vector_file, int index_current) {
  /*Iterate through vector_file to find SECTION_HEAD*/
  for (; index_current >= 0; --index_current) {
      /*Clean file strings to ensure matches*/
      std::string string_file = stringClean(vector_file.at(index_current), true, true, false);
      /*Found SECTION_HEAD*/
      if (string_file.find(SECTION_HEAD) == 0 && string_file != SECTION_END ) {
          return index_current;
        }
      /*Found section end, skip over section*/
      /*Get index_current and check if error*/
      if (string_file == SECTION_END &&
          (index_current = fileSectionHeadOf(vector_file, index_current - 1)) == FILE_ERROR) {
          return FILE_ERROR;
        }
    }
  return FILE_ERROR;
}

std::vector<std::string> dirList(const std::string& dir_path) {
  std::vector<std::string> vector_out;
  for (const auto& file : std::filesystem::directory_iterator(dir_path)) {
      if (file.is_directory()) {
          vector_out.push_back(stringReplace(file.path(), dir_path, ""));
        }
    }
  return vector_out;
}

std::vector<std::string> fileClean(std::vector<std::string> vector_file, const bool flag_comment, const bool flag_trim,
                                   const bool flag_space, const bool flag_empty) {
  for (int i = 0; i < static_cast<int>(vector_file.size()); ++i) {
      /*Remove leading/trailing white spaces, comments, and internal white spaces from line*/
      if (flag_comment|| flag_trim || flag_space ) {
          vector_file[i] = stringClean(vector_file.at(i), flag_comment, flag_trim, flag_space);
        }
      /*Remove empty lines*/
      if (flag_empty && vector_file.at(i).empty()) {
          vector_file.erase(vector_file.begin() + i);
          --i;
        }
    }
  return vector_file;
}

std::vector<std::string> fileFormat(std::vector<std::string> vector_file) {
  /*Clean vector_file from leading/trailing spaces and empty lines*/
  vector_file = fileClean(vector_file, false, true, false, true);

  /*Format vector_file with appropriate tabs and empty lines*/
  int tabs = 0;
  for (int i = 0; i < static_cast<int>(vector_file.size()); ++i) {
      /*Found SECTION_END, update tabs*/
      if (stringClean(vector_file.at(i), true, true, false) == SECTION_END) {
          --tabs;
          vector_file.insert(vector_file.begin() + i + 1, std::string());
        }
      /*Format line with tabs*/
      for (int j = 0; j < tabs; ++j) {
          vector_file[i].insert(0, "\t");
        }
      /*Found SECTION_HEAD, update tabs*/
      if (stringClean(vector_file.at(i), true, true, false).find(SECTION_HEAD) == 0 &&
          stringClean(vector_file.at(i), true, true, false) != SECTION_END) {
          ++tabs;
        }
    }
  return vector_file;
}

std::vector<std::string> fileList(const std::string& dir_path, const std::string& file_pattern) {
  std::vector<std::string> vector_out;
  for (const auto& file : std::filesystem::directory_iterator(dir_path)) {
      if (file.is_regular_file() &&
          (stringIsMatch(file_pattern.c_str(), file.path().filename().c_str()) || file_pattern.empty())) {
          vector_out.push_back(file.path().filename());
        }
    }
  return vector_out;
}

std::vector<std::string> fileRead(const std::string& path_in) {
  std::vector<std::string> vector_out;

  /*Read file line by line if found*/
  std::ifstream file_in(path_in.c_str());
  if (file_in) {
      std::string string_in;
      while (std::getline(file_in, string_in)) {
          vector_out.push_back(string_in);
        }
    }

  file_in.close();
  return vector_out;
}

std::vector<std::string> fileSection(const std::vector<std::string>& vector_file, const std::vector<std::string>& vector_section) {
  int index_current = 0;
  int index_end = static_cast<int>(vector_file.size());

  /*If nested sections update index_current and index_end*/
  if (!vector_section.empty()) {
      /*Get index_current and check if error*/
      if ((index_current = fileSectionHead(vector_file, vector_section)) == FILE_ERROR) {
          return std::vector<std::string>();
        }
      /*Returned value is section start, move to first index of section*/
      ++index_current;

      /*Get index_end and check if error*/
      if ((index_end = fileSectionEndOf(vector_file, index_current)) == FILE_ERROR) {
          return std::vector<std::string>();
        }
    }

  /*Return all lines between index_current and index_end*/
  return std::vector<std::string>(vector_file.begin() + index_current, vector_file.begin() + index_end);
}

std::vector<std::string> fileSectionList(const std::vector<std::string>& vector_file) {
  std::vector<std::string> vector_out;
  for (int i = 0; i < static_cast<int>(vector_file.size()); ++i) {
      /*Clean file strings to ensure matches for section checks*/
      std::string string_file = stringClean(vector_file.at(i), true, true, false);
      /*Found section head*/
      if (string_file.find(SECTION_HEAD) == 0 && string_file != SECTION_END) {
          vector_out.push_back(stringReplace(vector_file.at(i), SECTION_HEAD, std::string()));
          /*Get index_current of end of section and check if error*/
          if ((i = fileSectionEndOf(vector_file, i + 1)) == FILE_ERROR) {
              return std::vector<std::string>();
            }
        }
    }
  return vector_out;
}

std::vector<std::string> fileSectionReplace(std::vector<std::string> vector_file, const std::vector<std::string>& vector_section,
                                            const std::vector<std::string>& vector_replace) {
  int index_current = 0;
  int index_end = vector_file.size();

  /*If nested sections update index_current and index_end*/
  if (!vector_section.empty()) {
      /*Get index_current and check if error*/
      if ((index_current = fileSectionHead(vector_file, vector_section)) == FILE_ERROR) {
          return std::vector<std::string>();
        }
      /*Returned value is section start, move to first index of section*/
      ++index_current;

      /*Get index_end and check if error*/
      if ((index_end = fileSectionEndOf(vector_file, index_current)) == FILE_ERROR) {
          return std::vector<std::string>();
        }
    }

  /*Erase existing section lines*/
  vector_file.erase(vector_file.begin() + index_current, vector_file.begin() + index_end);

  /*Insert vector_replace lines*/
  vector_file.insert(vector_file.begin() + index_current, vector_replace.begin(), vector_replace.end());
  return vector_file;
}


std::vector<std::string> fileSectionSort(const std::vector<std::string>& vector_file) {
  /*Get list of sections in vector_file*/
  std::vector<std::string> vector_sections = fileSectionList(vector_file);

  /*Sort vector_sections to alphabetical order*/
  std::sort(vector_sections.begin(), vector_sections.end(), stringIsAlphabetic);

  /*Format vector_out with reordered vector_sections*/
  std::vector<std::string> vector_out;
  for (const std::string& string_section : vector_sections) {
      vector_out.push_back(SECTION_HEAD + string_section);
      std::vector<std::string> vector_temp = fileSection(vector_file, {string_section});
      vector_out.insert(vector_out.end(), vector_temp.begin(), vector_temp.end());
      vector_out.push_back(SECTION_END);
    }
  return vector_out;
}
