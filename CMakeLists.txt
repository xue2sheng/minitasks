cmake_minimum_required (VERSION 3.5)
project (minitasks)

# Boost libraries required
set(Boost_USE_STATIC_LIBS ON CACHE BOOL "use static libraries from Boost")
set(Boost_USE_STATIC_RUNTIME ON CACHE BOOL "use static runtime from Boost")
set(Boost_USE_MULTITHREADED ON)
find_package( Boost )
if( Boost_FOUND )
  message(STATUS "Boost LIBRARIES: ${Boost_LIBRARIES}")
else()
  message(FATAL_ERROR "Boost libraries requied")
endif()

# Different compiler support
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -static-libstdc++ -static-libgcc -g") 
  message(STATUS "GNU FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  message(STATUS "Clang FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -stdlib=libc++ -g") 
  message(STATUS "Apple Clang FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  message(STATUS "Intel FLAGS: ${CMAKE_CXX_FLAGS}")
else ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message(FATAL_ERROR "Not supported") 
endif()

# Extract info.yaml versions
set(INFO_YAML "${CMAKE_SOURCE_DIR}/info.yaml")
message(STATUS "INFO_YAML: ${INFO_YAML}")
file(READ "${INFO_YAML}" INFO)
string(REGEX REPLACE ";" "\\\\;" INFO "${INFO}")
string(REGEX REPLACE "\n" ";" INFO "${INFO}")
foreach(LINE "${INFO}")
 string(REGEX MATCH "[ ]*VERSION_INFO: .*" VERSION_LINE "${LINE}")
 if(DEFINED VERSION_LINE)
     string(REGEX REPLACE ";" "" VERSION_LINE "${VERSION_LINE}")
     string(STRIP "${VERSION_LINE}" VERSION_LINE)
 else()
     message(FATAL_ERROR "VERSION_INFO not found at ${INFO_YAML}")
 endif()
endforeach(LINE "${INFO}")
 
# Add GIT info
execute_process(
  COMMAND git log -1 --format=%H 
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} 
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(VERSION_INFO "${VERSION_LINE}_${GIT_COMMIT_HASH}")
message(STATUS "${VERSION_INFO}")

# Create .hpp version file
set(VERSION_HPP_IN "${CMAKE_SOURCE_DIR}/src/version.hpp.in")
set(VERSION_HPP_OUT "${CMAKE_SOURCE_DIR}/src/version.hpp")

configure_file(${VERSION_HPP_IN} ${VERSION_HPP_OUT})

# Get ready for unit tests 
enable_testing()

# recursive call to code folders
add_subdirectory(src)
add_subdirectory(test)
