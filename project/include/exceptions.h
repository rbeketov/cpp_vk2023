#pragma once // NOLINT

#include <exception>
#include "pars_movies.h"



namespace parse {
class ParseException: public std::exception {
 public:
  explicit ParseException(const std::string& msg)
      : m_msg(msg) {}

  const char* what() const noexcept override {
    return m_msg.c_str();
  }

 private:
  std::string m_msg;
};

class InvalidPath: public ParseException {
 public:
  InvalidPath(std::string path)
      : ParseException("Cannot open file " + path) {}
};

class InvalidArgumentsCnt: public ParseException {
 public:
  explicit InvalidArgumentsCnt(int numArg)
      : ParseException("Invalid arguments: " + std::to_string(numArg-1) + " were submitted, but 4 were required") {}
};

class InvalidArguments: public ParseException {
 public:
  InvalidArguments()
  : ParseException(R"(Invalid arguments at start
                    Example:
                    ./pars --basicsDump={path} --ratingsDump={path} --akasDump={path} --numMin={unsign})") {}
};

class InvalidArgumentsNum: public ParseException {
 public:
  InvalidArgumentsNum()
      : ParseException("Invalid \"numMin\" argument") {}
};

class InvalidDumpTitle: public ParseException {
 public:
  explicit InvalidDumpTitle(const std::string& path)
      : ParseException("Invalid dump: " + path) {}
};

}  // namespace parse
