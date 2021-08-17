#include <algorithm>
#include <chrono>
#include <cstring>
#include <cxxabi.h>
#include <iomanip>
#include <math.h>
#include <sstream>

#include "function_string.hpp"

bool stringIsAlphabetic(const std::string& string_1, const std::string& string_2) {
  return static_cast<bool>(stringToLower(string_1) < stringToLower(string_2));
}

bool stringIsMatch(const char* pattern_in, const char* string_in) {
  /*End of string, done comparing*/
  if (*pattern_in == '\0' && *string_in == '\0') {
      return true;
    }

  /*Check characters after '*' are present in string_in*/
  /*Assume pattern_in does not contain consecutive '*' characters*/
  if (*pattern_in == '*' && *(pattern_in + 1) != '\0' && *string_in == '\0') {
      return false;
    }

  /*Check if pattern_in contains '?' or curent characters of both strings match*/
  if (*pattern_in == '?' || *pattern_in == *string_in) {
      return stringIsMatch(pattern_in + 1, string_in + 1);
    }

  /*Check if pattern_in contains '*' and consider two possibilities*/
  /*1) Check current character of string_in*/
  /*2) Ignore current character of string_in*/
  if (*pattern_in == '*') {
      return stringIsMatch(pattern_in + 1, string_in) || stringIsMatch(pattern_in, string_in + 1);
    }
  return false;
}

bool stringIsNum(const std::string& string_in) {
  try {
    std::stod(string_in);
    return true;
  }
  catch (...) {
    return false;
  }
}

bool stringToChar(const std::string& string_in, char* array_out, const int array_size) {
  /*Check array_out is big enough to hold string*/
  if (string_in.size() > static_cast<unsigned int>(array_size + 1)) {
      return false;
    }

  /*Copy string to array_out + null terminator*/
  string_in.copy(array_out, array_size);
  array_out[string_in.size()] = '\0';
  return true;
}

double stringToNum(const std::string& string_in) {
  try {
    /*Return value of string as a double*/
    return std::stod(string_in);
  }
  catch (...) {
    /*Return nan if string is not number*/
    return std::numeric_limits<double>::quiet_NaN();
  }
}

std::string stringClean(std::string string_text, const bool flag_comment, const bool flag_trim, const bool flag_space) {
  /*Remove comment from string*/
  if (flag_comment && string_text.find(DELIMITER_COMMENT) != std::string::npos) {
      string_text.resize(string_text.find(DELIMITER_COMMENT));
    }
  /*Remove leading/trailing white spaces from string*/
  if (flag_trim) {
      /*Trim leading white spaces*/
      string_text.erase(string_text.begin(), std::find_if(string_text.begin(), string_text.end(),
                                                          [](unsigned char ch) {return !std::isspace(ch);}));

      /*Trim trailing white spaces*/
      string_text.erase(std::find_if(string_text.rbegin(), string_text.rend(),
                                     [](unsigned char ch) {return !std::isspace(ch);}).base(), string_text.end());
    }
  /*Remove all white spaces from string*/
  if (flag_space) {
      /*Get the end of the string or the start of comments section to iterate up to*/
      std::string::iterator string_end = string_text.find(DELIMITER_COMMENT) == std::string::npos ?
            string_text.end() : string_text.begin() + string_text.find(DELIMITER_COMMENT);

      string_text.erase(std::remove_if(string_text.begin(), string_end, [](char ch) {
          return std::isspace<char>(ch, std::locale::classic());}), string_end);
    }
  return string_text;
}

std::string stringColorHSL(const double hue, const double saturation, const double luminosity) {
  /*Convert HSL values to RGB*/
  double C = (1.0 - std::fabs(2.0 * luminosity / 100.0 - 1.0)) * (saturation / 100.0);
  double X = C * (1.0 - std::fabs(std::fmod(hue / 60.0, 2.0) - 1.0));
  double m = (luminosity / 100.0) - (C / 2.0);
  int red, green, blue;
  if (hue >= 0 && hue < 60) {
      red = static_cast<int>((C + m) * 255);
      green = static_cast<int>((X + m) * 255);
      blue = static_cast<int>(m * 255);
  }
  else if (hue >= 60 && hue < 120) {
      red = static_cast<int>((X + m) * 255);
      green = static_cast<int>((C + m) * 255);
      blue = static_cast<int>(m * 255);
  }
  else if (hue >= 120 && hue < 180) {
      red = static_cast<int>(m * 255);
      green = static_cast<int>((C + m) * 255);
      blue = static_cast<int>((X + m) * 255);
  }
  else if (hue >= 180 && hue < 240) {
      red = static_cast<int>(m * 255);
      green = static_cast<int>((X + m) * 255);
      blue = static_cast<int>((C + m) * 255);
  }
  else if (hue >= 240 && hue < 300) {
      red = static_cast<int>((X + m) * 255);
      green = static_cast<int>(m * 255);
      blue = static_cast<int>((C + m) * 255);
  }
  else {
      red = static_cast<int>((C + m) * 255);
      green = static_cast<int>(m * 255);
      blue = static_cast<int>((X + m) * 255);
  }

  /*Get Hex from RGB*/
  return stringColorRGB(red, green, blue);
}

std::string stringColorRGB(const int red, const int green, const int blue) {
  std::stringstream string_out;
  string_out << "#";
  string_out << std::setfill('0') << std::setw(2) << std::hex << red;
  string_out << std::setfill('0') << std::setw(2) << std::hex << green;
  string_out << std::setfill('0') << std::setw(2) << std::hex << blue;
  return string_out.str();
}

std::string stringComment(std::string string_text) {
  if (string_text.find(DELIMITER_COMMENT) == std::string::npos) {
      return std::string();
    }
  string_text.erase(0, string_text.find(DELIMITER_COMMENT) + std::string(DELIMITER_COMMENT).size());
  return string_text;
}

std::string stringDateTime(const std::string& string_format) {
  std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::stringstream time_stream;
  time_stream << std::put_time(std::localtime(&current_time), string_format.c_str());
  return time_stream.str();
}

std::string stringDemangle(const char* string_in) {
  /*Arbitrary value to eliminate compiler warning*/
  int status = -4;

  /*Enable c++11 by passing the flag -std=c++11 to g++*/
  std::unique_ptr<char, void(*)(void*)> res {
      abi::__cxa_demangle(string_in, NULL, NULL, &status),
      std::free
  };

  return std::string((status==0) ? res.get() : string_in);
}

std::string stringHTML(std::string string_text, const std::string& color_in, const bool flag_bold) {
  string_text = stringReplace(string_text, "<", "&lt;");
  string_text = stringReplace(string_text, ">", "&gt;");
  string_text = stringReplace(string_text, "\n", "<br>");
  if (!color_in.empty()) {
      string_text.insert(0, "<font color = " + color_in + ">");
      string_text.append("</font>");
    }
  if (flag_bold) {
      string_text.insert(0, "<b>");
      string_text.append("</b>");
    }
  return string_text;
}

std::string stringJoin(const std::vector<std::string>& vector_in, const std::string& string_delim) {
  std::string string_out;
  for (const std::string& string_in : vector_in) {
      string_out.append(string_in);

      /*Append string_delim as long as string_in is not the last element of vector_in*/
      if (&string_in != &vector_in.back()) {
          string_out.append(string_delim);
        }
    }
  return string_out;
}

std::string stringReplace(std::string string_source, const std::string& string_find, const std::string& string_replace) {
  size_t index = 0;
  while ((index = string_source.find(string_find, index)) != std::string::npos) {
      string_source.replace(index, string_find.size(), string_replace);
      index += string_replace.size();
    }
  return string_source;
}

std::string stringToLower(std::string string_text) {
  /*Got this from stackOverflow, it works beautifully but not entirely sure how*/
  std::transform(string_text.begin(), string_text.end(), string_text.begin(), [](unsigned char ch){return std::tolower(ch);});
  return string_text;
}

std::vector<char> stringToBytes(const std::string& string_in) {
  return std::vector<char>(string_in.begin(), string_in.end());
}

std::vector<char> structToBytes(void* data_in, const int data_size) {
  std::vector<char> bytes_out(data_size);
  std::memcpy(bytes_out.data(), data_in, data_size);
  return bytes_out;
}

std::vector<std::string> stringSplit(const std::string& string_in, const std::string& string_delim) {
  if (string_in.empty()) {
      return std::vector<std::string>();
    }
  std::vector<std::string> vector_out;
  size_t start_pos = 0, end_pos;
  while ((end_pos = string_in.find(string_delim, start_pos)) != std::string::npos) {
      vector_out.push_back(string_in.substr(start_pos, end_pos - start_pos));
      start_pos = end_pos + string_delim.size();
    }
  vector_out.push_back(string_in.substr(start_pos, end_pos - start_pos));
  return vector_out;
}
