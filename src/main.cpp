#include <iostream>
#include <string>
#include <dlfcn.h>

#include "boost/program_options.hpp"
#include "main.hpp"

int main(int argc, char** argv)
{
    try
    {
        std::string plugin_path;
        std::string plugin_name;
        
	// Define and parse the program options
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
        ("help", "Print help messages")
        ("location,L", po::value<std::string>(&plugin_path)->default_value("."), "where libraries are located")
        ("plugin,P", po::value<std::string>(&plugin_name)->default_value("basic"), "name of the plugin to be loaded");
      
        // command line arguments
        
        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm); // can throw
            
            // --help option
            if ( vm.count("help") )
            {
                std::cout << "Basic Command Line Parameter App" << std::endl
                << desc << std::endl;
                return SUCCESS;
            }
            
            // throws on error, so do after help in case there are any problems
            po::notify(vm);
        }
        catch(po::error& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
        
        // application code here
        
        // load basic library
        std::string plugin = plugin_path + DIR_SEP + LIB_PRE + plugin_name + LIB_EXT;
        void* library = dlopen(plugin.c_str(), RTLD_NOW);
        if (!library) {
            std::cerr << "Cannot load library: " << dlerror() << '\n';
            return ERROR_DYNAMIC_LIBRARY;
        }
        
        // reset errors
        dlerror();
        
        // load the symbols
	using basic = int (*)();

        basic handle = (basic) dlsym(library, "basic");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
            return ERROR_DYNAMIC_LIBRARY;
        }
        
        // use the class
        std::cout << "The value is: " << handle() << '\n';
        
        // unload the library
        dlclose(library);
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached the top of main: "
        << e.what() << ", application will now exit" << std::endl; 
        return ERROR_UNHANDLED_EXCEPTION; 
    }
    
    return SUCCESS; 
    
} // main
