#ifndef PROGRAM_OPTIONS_HPP
#define PROGRAM_OPTIONS_HPP

#include <string> 
#include "base_exception.hpp" 

class ProgramOptions final
{
public:

    struct ErrorInCommandLine final : public BaseException {
	inline explicit ErrorInCommandLine(const std::string& msg) 
	: BaseException(msg, ERROR_IN_COMMANDLINE) {}
    };

    struct ErrorInConfigurationFile final : public BaseException {
	inline explicit ErrorInConfigurationFile(const std::string& msg) 
	: BaseException(msg, ERROR_IN_CONFIGURATION_FILE) {}
    };

    struct ErrorConfigurationFileNotFound final : public BaseException {
	inline explicit ErrorConfigurationFileNotFound(const std::string& msg) 
	: BaseException(msg, ERROR_CONFIGURATION_FILE_NOT_FOUND) {}
    };

    struct Help final : public BaseException {
	inline explicit Help(const std::string& msg) : BaseException(msg) {}
    };

    struct Version final : public BaseException {
	inline explicit Version(const std::string& msg) : BaseException(msg) {}
    };

  // it can throw
  explicit ProgramOptions(int argc, char** argv);

  // Getters
  inline std::string plugin() const { return plugin_; }
  inline std::string symbol() const { return symbol_; }
  inline std::string config() const { return config_; }
  inline int port() const { return port_; }
  inline std::string host() const { return host_; }
  inline std::string auxiliar() const { return auxiliar_; }

private:
  std::string plugin_ {""};
  std::string symbol_ {""};
  std::string config_ {""};
  int port_ {0};
  std::string host_ {""};
  std::string auxiliar_ {""};
};

#endif // PROGRAM_OPTIONS_HPP