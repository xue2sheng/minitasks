#ifndef MAIN_CPP
#define MAIN_CPP

// library endings

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

// return values

static constexpr size_t ERROR_IN_COMMAND_LINE = 1;
static constexpr size_t SUCCESS = 0;
static constexpr size_t ERROR_UNHANDLED_EXCEPTION = 2;
static constexpr size_t ERROR_DYNAMIC_LIBRARY = 3;

#endif // MAIN_CPP
