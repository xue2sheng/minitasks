#ifndef PROGRAM_OPTIONS_HPP
#define PROGRAM_OPTIONS_HPP

#include <string> 
#include <sstream>
#include <exception> 
#include "boost/program_options.hpp"

class ProgramOptions final
{
public:

    struct BaseException : public std::exception {
	std::string message {""};
	inline explicit BaseException(const std::string& msg) : message(msg) {}
	inline virtual const char* what() const noexcept override { return message.c_str(); }
    };

    struct ErrorInCommandLine final : public BaseException {
	inline explicit ErrorInCommandLine(const char *msg) : BaseException(msg) {}
    };

    struct Help final : public BaseException {
	inline explicit Help(const boost::program_options::options_description& desc) 
	: BaseException("Basic Command Line Parameter App\n") 
	{ 
	    std::ostringstream oss; oss << desc; message += oss.str();
	}
    };

    struct Version final : public BaseException {
	inline explicit Version(const char* msg) : BaseException(msg) {}
    };

  // it can throw
  explicit ProgramOptions(int argc, char** argv);

  // Getters
  inline std::string plugin_path() const { return plugin_path_; }
  inline std::string plugin_name() const { return plugin_name_; }
  inline std::string plugin() const { return plugin_; }

private:
 std::string plugin_path_ {"."};
 std::string plugin_name_ {"basic"};
 std::string plugin_ {""};
};

#endif // PROGRAM_OPTIONS_HPP