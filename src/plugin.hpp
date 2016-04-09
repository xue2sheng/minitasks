#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <string>
#include "base_exception.hpp"

class Plugin
{
public:
    // load the symbols
    using basic = int (*)(int);

    struct ErrorDynamicLibraryOpen final : public BaseException {
	inline explicit ErrorDynamicLibraryOpen(const char* msg) 
	: BaseException(msg, ERROR_DYNAMIC_LIBRARY_OPEN) {}
    };

    struct ErrorDynamicLibrarySym final : public BaseException {
	inline explicit ErrorDynamicLibrarySym(const char* msg) 
	: BaseException(msg, ERROR_DYNAMIC_LIBRARY_SYMBOL) {}
    };

    // it can throw
    explicit Plugin(const std::string&); 
  
    // shouldn't throw
    virtual ~Plugin();

    // getters
    inline basic handle() const { return handle_; } 

private:
    basic handle_ {nullptr}; 
    void* library_ {nullptr};
}; // class 

#endif // PLUGIN_HPP