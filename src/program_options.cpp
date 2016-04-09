#include "version.hpp"
#include "program_options.hpp"

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
  
ProgramOptions::ProgramOptions(int argc, char** argv)  
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
            if ( vm.count("help") ) { throw Help{desc}; }
            
            // --version option
	    else if ( vm.count("version") ) { throw Version{VERSION_INFO}; }

            // throws on error, so do after help in case there are any problems
	    else { po::notify(vm); }
        }
        catch(const po::error& e)
        {
	    throw ErrorInCommandLine{e.what()};
        }
        
        // load basic library
        plugin_ = plugin_path_ + DIR_SEP + LIB_PRE + plugin_name_ + LIB_EXT;
    
} // constructor
