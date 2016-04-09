#include <sstream>
#include <fstream>
#include "boost/program_options.hpp"
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
        namespace po = boost::program_options;

        // process configuration file
        po::options_description config_desc("Configuration file options");	
        config_desc.add_options()
	// section [server]
        ("server.port,P", po::value<int>(&port_)->default_value(5000), "server port number to connect")
        ("server.host,H", po::value<std::string>(&host_)->default_value("localhost"), "server host address to connect")
	// section [auxiliar]
        ("auxiliar.symbol,X", po::value<std::string>(&auxiliar_)->default_value("auxiliar"), "auxiliar symbol in the plugin");

	// process command line
        std::string plugin_path;
        std::string plugin_name;

        po::options_description desc("Commandline options");
        desc.add_options()
        ("help,h", "Print help messages")
        ("version,v", "Print version messages")
        ("location,l", po::value<std::string>(&plugin_path)->default_value("."), "where libraries are located")
        ("plugin,p", po::value<std::string>(&plugin_name)->default_value("basic"), "name of the plugin to be loaded")
        ("symbol,s", po::value<std::string>(&symbol_)->default_value("basic"), "symbol to be found in plugin")
	("config,c", po::value<std::string>(&config_)->default_value("basic.ini"), "configuration file");
      
        // command line arguments
        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm); // can throw
            
            // --help option
            if ( vm.count("help") ) { 
	        std::ostringstream oss; 
	        oss << desc; 
		throw Help{oss.str()}; 
	    }
            
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
        plugin_ = plugin_path + DIR_SEP + LIB_PRE + plugin_name + LIB_EXT;

	// relative path if is not an absolute path starting by DIR_SEP
	if( config_[0] != DIR_SEP[0] ) { config_ = plugin_path + DIR_SEP + config_; }
   
        // configuration file arguments
	if ( vm.count("config") )
	{
	   std::ifstream ifs{config_};
           if (ifs)
	   {
              po::variables_map config_vm;
              try
              {
	        po::store(po::parse_config_file(ifs,config_desc),config_vm);

	        // throws on error, so do after help in case there are any problems
	        po::notify(config_vm); 
              }
              catch(const po::error& e)
              {
	       throw ErrorInConfigurationFile{e.what()};
              }
	   } else { 
	       throw ErrorConfigurationFileNotFound{config_ + " not found"}; 
	   }

	} // config
	
} // constructor
