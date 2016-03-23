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
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -stdlib=libc++ -rpath /opt/clang/lib -g") 
  message(STATUS "Clang FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -stdlib=libc++ -g") 
  message(STATUS "Apple Clang FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  message(STATUS "Intel FLAGS: ${CMAKE_CXX_FLAGS}")
else ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message(FATAL_ERROR "Not supported") 
endif()

# Extract info.yaml version info 
set( VERSION_LINE "VERSION_INFO: 0.0.1" )

#########################
######################### 
set( WILDCARD "pepe" )
set( DOXYFILE_PROJECT_NAME "${CMAKE_PROJECT_NAME}")
set( DOXYFILE_PROJECT_NUMBER "999")
set( CMAKE_GIT_COMMIT_HASH "${VERSION_INFO}")
set( DOXYFILE_PROJECT_BRIEF "${WILDCARD}")
set( DOXYFILE_INPUT00 "${WILDCARD}")
set( DOXYFILE_INPUT01 "${WILDCARD}")
set( DOXYFILE_INPUT02 "${WILDCARD}")
set( DOXYFILE_INPUT03 "${WILDCARD}")
set( DOXYFILE_INPUT04 "${WILDCARD}")
set( DOXYFILE_INPUT05 "${WILDCARD}")
set( DOXYFILE_INPUT06 "${WILDCARD}")
set( DOXYFILE_INPUT07 "${WILDCARD}")
set( DOXYFILE_INPUT08 "${WILDCARD}")
set( DOXYFILE_INPUT09 "${WILDCARD}")
set( DOXYFILE_INPUT10 "${WILDCARD}")
set( DOXYFILE_INPUT11 "${WILDCARD}")
set( DOXYFILE_INPUT12 "${WILDCARD}")
set( DOXYFILE_INPUT13 "${WILDCARD}")
set( DOXYFILE_INPUT14 "${WILDCARD}")
set( DOXYFILE_INPUT15 "${WILDCARD}")
set( DOXYFILE_INPUT16 "${WILDCARD}")
set( DOXYFILE_INPUT17 "${WILDCARD}")
set( DOXYFILE_INPUT18 "${WILDCARD}")
set( DOXYFILE_INPUT19 "${WILDCARD}")
set( LOCAL_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
set( DOXYFILE_INPUT_FILTER "${CMAKE_BINARY_DIR}/md_filter.awk")
set( DOXYFILE_FILTER_PATTERNS "${WILDCARD}")
set( CMAKE_HEADER_OUT "${CMAKE_BINARY_DIR}/header.tex")
###################################
set( GIT_SYSTEM "${WILDCARD}")
set( GIT_MODULES_STATUS "${WILDCARD}")
set( CMAKE_GIT_DETAILS "${WILDCARD}")
set( DOXYFILE_PROJECT_NUMBER_CORE "888")
set( CMAKE_GIT_DETAILS_CORE "${WILDCARD}")
set( DOXYFILE_PROJECT_NUMBER_BASE "777")
set( CMAKE_GIT_DETAILS_BASE "${WILDCARD}")
set( DOXYFILE_PROJECT_NUMBER_UI "666")
set( CMAKE_GIT_DETAILS_UI "${WILDCARD}")
set( DOXYFILE_PROJECT_NUMBER_PERSIST "555")
set( CMAKE_GIT_DETAILS_PERSIST "${WILDCARD}")

#########################
######################### 

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
file(COPY ${VERSION_HPP_OUT} DESTINATION "${CMAKE_SOURCE_DIR}/test")

# Create templates for documentation files
set(DOXYFILE_IN "${CMAKE_SOURCE_DIR}/doc/Doxyfile.in")
set(DOXYFILE_OUT "${CMAKE_BINARY_DIR}/Doxyfile")
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT})
set(HEADER_TEX_IN "${CMAKE_SOURCE_DIR}/doc/header.tex.in")
set(HEADER_TEX_OUT "${CMAKE_BINARY_DIR}/header.tex")
configure_file(${HEADER_TEX_IN} ${HEADER_TEX_OUT})
set(MD_FILTER_AWK_IN "${CMAKE_SOURCE_DIR}/doc/md_filter.awk.in")
set(MD_FILTER_AWK_OUT "${CMAKE_BINARY_DIR}/md_filter.awk")
configure_file(${MD_FILTER_AWK_IN} ${MD_FILTER_AWK_OUT})
 
# Get ready for unit tests 
enable_testing()

# recursive call to code folders
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)
