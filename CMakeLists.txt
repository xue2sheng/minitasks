cmake_minimum_required (VERSION 3.5)
project (minitasks)

# Get ready to used non default installed compilers/libraries
if(DEFINED RPATH_LIB64)
 set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wl,-rpath -Wl,${RPATH_LIB64} -static-libstdc++ -static-libgcc -g")
else(DEFINED RPATH_LIB64)
 set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -static-libstdc++ -static-libgcc -g")
endif(DEFINED RPATH_LIB64)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
