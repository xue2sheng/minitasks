#include <string>
#include <dlfcn.h>
#include "plugin.hpp"

Plugin::Plugin(const std::string& path)
{
        // load basic library
        library_ = dlopen(path.c_str(), RTLD_NOW);
        const char* error_open = dlerror();
        if (!library_) { throw  ErrorDynamicLibraryOpen(error_open); }
}

Plugin::basic Plugin::handle(const std::string& symbol)
{
	// use a local cache
	if( last_symbol != symbol )
	{
          // reset errors
          dlerror();

	  // refresh cache
          handle_ = (basic) dlsym(library_, symbol.c_str());
          const char* error_sym = dlerror();
          if (error_sym) { throw  ErrorDynamicLibrarySym(error_sym); }
	  last_symbol = symbol;
	}

	return handle_;
} 

Plugin::~Plugin()
{
   if(library_) { dlclose(library_); library_ = nullptr; };
}
