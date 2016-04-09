#include <iostream>

#include "program_options.hpp"
#include "plugin.hpp"

int main(int argc, char** argv)
{
    try
    {
	Plugin plugin {ProgramOptions(argc,argv).plugin()};

	std::cout << "Plugin value: " << plugin.handle()(5) << std::endl;
    }
    catch(const BaseException& e)
    {
	return e.printout();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Unhandled Exception at main: " << e.what() << std::endl; 
        return ERROR_UNHANDLED_EXCEPTION; 
    }
    
    return SUCCESS; 
    
} // main
