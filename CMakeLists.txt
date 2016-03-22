cmake_minimum_required (VERSION 3.5)
project (minitasks)

# Get ready to used non default installed compilers/libraries
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -static-libstdc++ -static-libgcc -g")
if(DEFINED RPATH_LIB64)
 set(CMAKE_CXX_FLAGS "-Wl,-rpath -Wl,${RPATH_LIB64} ${CMAKE_CXX_FLAGS}")
endif(DEFINED RPATH_LIB64)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
