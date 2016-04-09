#include <iostream>
#include <string>
#include <dlfcn.h>

#include "program_options.hpp"
#include "eidheim/server_http.hpp"
#include "main.hpp"

int main(int argc, char** argv)
{
    try
    {
        ProgramOptions program_options(argc,argv);

        // load basic library
        void* library = dlopen(program_options.plugin().c_str(), RTLD_NOW);
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
    catch(const ProgramOptions::Help& e)
    {
	std::cout << e.what() << std::endl;
	return SUCCESS;
    }
    catch(const ProgramOptions::Version& e)
    {
	std::cout << e.what() << std::endl;
	return SUCCESS;
    }
    catch(const ProgramOptions::ErrorInCommandLine& e)
    {
	std::cerr << e.what() << std::endl;
	return ERROR_IN_COMMAND_LINE;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Unhandled Exception reached the top of main: "
        << e.what() << ", application will now exit" << std::endl; 
        return ERROR_UNHANDLED_EXCEPTION; 
    }
    
    return SUCCESS; 
    
} // main
