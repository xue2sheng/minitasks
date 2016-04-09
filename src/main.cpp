#include <iostream>

#include "program_options.hpp"
#include "plugin.hpp"

int main(int argc, char** argv)
{
    try
    {
	ProgramOptions options(argc,argv);
	Plugin plugin {options.plugin()};

	std::cout << "Plugin value: " << plugin.handle(options.symbol())(5) << std::endl;
	std::cout << "Host:Port = " << options.host() << ":" << options.port() << std::endl;
	std::cout << "Auxiliar.symbol = " << options.auxiliar() << std::endl;
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
