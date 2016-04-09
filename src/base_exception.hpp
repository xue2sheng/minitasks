#ifndef BASE_EXCEPTION_HPP
#define BASE_EXCEPTION_HPP

#include <exception>
#include <string>
#include <iostream>

// return values
static constexpr size_t SUCCESS = 0;
static constexpr size_t ERROR_IN_COMMANDLINE = 1;
static constexpr size_t ERROR_UNHANDLED_EXCEPTION = 2;
static constexpr size_t ERROR_DYNAMIC_LIBRARY_OPEN = 3;
static constexpr size_t ERROR_DYNAMIC_LIBRARY_SYMBOL = 4;
static constexpr size_t ERROR_IN_CONFIGURATION_FILE = 5;
static constexpr size_t ERROR_CONFIGURATION_FILE_NOT_FOUND = 6;

class BaseException : public std::exception {
  std::string message {""};
  int code {SUCCESS};
public:
  inline explicit BaseException(const std::string& msg, int c = SUCCESS) 
  : message{msg}, code{c} {}
  inline virtual const char* what() const noexcept override { return message.c_str(); }
  inline virtual int printout() const noexcept { 
      if(SUCCESS == code) { std::cout << message << std::endl; }
      else { std::cerr << message << std::endl; }
      return code;
  }
};

#endif // BASE_EXCEPTION_HPP