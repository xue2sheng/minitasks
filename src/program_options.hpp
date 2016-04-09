#ifndef PROGRAM_OPTIONS_HPP
#define PROGRAM_OPTIONS_HPP

#include <string> 
#include "base_exception.hpp" 

class ProgramOptions final
{
public:

    struct ErrorInCommandLine final : public BaseException {
	inline explicit ErrorInCommandLine(const char* msg) 
	: BaseException(msg, ERROR_IN_COMMANDLINE) {}
    };

    struct Help final : public BaseException {
	inline explicit Help(const char* msg) : BaseException(msg) {}
    };

    struct Version final : public BaseException {
	inline explicit Version(const char* msg) : BaseException(msg) {}
    };

  // it can throw
  explicit ProgramOptions(int argc, char** argv);

  // Getters
  inline std::string plugin() const { return plugin_; }

private:
  std::string plugin_ {""};
};

#endif // PROGRAM_OPTIONS_HPP