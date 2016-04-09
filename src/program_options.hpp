#ifndef PROGRAM_OPTIONS_HPP
#define PROGRAM_OPTIONS_HPP

#include <string> 
#include <sstream>
#include <exception> 
#include "boost/program_options.hpp"
#include "version.hpp"

class ProgramOptions final
{
public:

 #if defined(__linux__) || defined(__sun__)
   static constexpr const char* LIB_PRE = "lib";
   static constexpr const char* LIB_EXT = ".so";
   static constexpr const char* DIR_SEP = "/";
 #elif defined(__APPLE__)
   static constexpr const char* LIB_PRE = "lib";
   static constexpr const char* LIB_EXT = ".dylib";
   static constexpr const char* DIR_SEP = "/";
 #else
   static constexpr const char* LIB_PRE = "";
   static constexpr const char* LIB_EXT = "";
   static constexpr const char* DIR_SEP = "";
 #endif

    class ErrorInCommandLine : public std::exception {
	std::string message;
    public:
	explicit ErrorInCommandLine(const char *msg) : message(msg) {}
	virtual const char* what() const noexcept override { return message.c_str(); }
    };
    class Help : public std::exception {
    	std::string message;
    public:
	explicit Help(const boost::program_options::options_description& desc) 
	{ 
	    std::ostringstream oss;
    	    oss << "Basic Command Line Parameter App" << std::endl << desc;
            message = oss.str();
	}
	virtual const char* what() const noexcept override { return message.c_str(); }
    };
    class Version : public std::exception {
    	std::string message;
    public:
	explicit Version(const std::string& msg) : message(msg) {}
	virtual const char* what() const noexcept override { return message.c_str(); }
    };

  // it can throw
  explicit ProgramOptions(int argc, char** argv)  
  {
	// Define and parse the program options
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
        ("help,h", "Print help messages")
        ("version,v", "Print version messages")
        ("location,L", po::value<std::string>(&plugin_path_)->default_value("."), "where libraries are located")
        ("plugin,P", po::value<std::string>(&plugin_name_)->default_value("basic"), "name of the plugin to be loaded");
      
        // command line arguments
        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm); // can throw
            
            // --help option
            if ( vm.count("help") ) { throw Help(desc); }
            
            // --version option
	    else if ( vm.count("version") ) { throw Version(VERSION_INFO); }

            // throws on error, so do after help in case there are any problems
	    else { po::notify(vm); }
        }
        catch(const po::error& e)
        {
	    throw ErrorInCommandLine(e.what());
        }
        
        // load basic library
        plugin_ = plugin_path_ + DIR_SEP + LIB_PRE + plugin_name_ + LIB_EXT;
    
  } // constructor

  // Getters
  std::string plugin_path() const { return plugin_path_; }
  std::string plugin_name() const { return plugin_name_; }
  std::string plugin() const { return plugin_; }

private:
 std::string plugin_path_ {"."};
 std::string plugin_name_ {"basic"};
 std::string plugin_ {""};
};

#endif // PROGRAM_OPTIONS_HPP