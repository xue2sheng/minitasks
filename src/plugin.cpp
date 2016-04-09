#include <string>
#include <dlfcn.h>
#include "plugin.hpp"

Plugin::Plugin(const std::string& path)
{
        // load basic library
        library_ = dlopen(path.c_str(), RTLD_NOW);
        const char* error_open = dlerror();
        if (!library_) { throw  ErrorDynamicLibraryOpen(error_open); }
        
        // reset errors
        dlerror();
        
        handle_ = (basic) dlsym(library_, "basic");
        const char* error_sym = dlerror();
        if (error_sym) { throw  ErrorDynamicLibrarySym(error_sym); }
} 

Plugin::~Plugin()
{
   if(library_) { dlclose(library_); };
}
