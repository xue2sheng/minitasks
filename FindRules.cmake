# Include version restriction on compilers and libraries

################################
#### Optional Documentation ####   
################################

## default deployment targets 
set(PDF_FILE ${CMAKE_SOURCE_DIR}/doc/${CMAKE_PROJECT_NAME}.pdf)
set(HTML_DIR ${CMAKE_SOURCE_DIR}/doc/html)

## default PDF header
set( DOXYFILE_PROJECT_NAME "Minitasks")
set( DOXYFILE_PROJECT_NUMBER "0.0.1")
set( DOXYFILE_PROJECT_BRIEF "Infrastructure to load small tasks and manage them")

############################
# Boost libraries required #
############################

find_package( Boost )
if( Boost_FOUND )

  if (Boost_VERSION VERSION_LESS 1.58.0)
     message(FATAL_ERROR "Boost version must be at least 1.58.0!")
  endif()

  set(Boost_USE_STATIC_LIBS ON CACHE BOOL "use static libraries from Boost")
  set(Boost_USE_STATIC_RUNTIME ON CACHE BOOL "use static runtime from Boost")
  set(Boost_USE_MULTITHREADED ON)

else()
  message(FATAL_ERROR "Boost libraries requied")
endif()

##############################
# Different compiler support #
##############################

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.2)
     message(FATAL_ERROR "GCC version must be at least 5.2!")
  endif()
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -static-libstdc++ -static-libgcc -g") 
  message(STATUS "GNU FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.8)
     message(FATAL_ERROR "Clang version must be at least 3.8!")
  endif()
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -stdlib=libc++ -Wl,-rpath,/opt/clang/lib -g") 
  message(STATUS "Clang FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
     message(FATAL_ERROR "Apple Clang version must be at least 7.0!")
  endif()
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -stdlib=libc++ -g") 
  message(STATUS "Apple Clang FLAGS: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  message(STATUS "Intel version: ${CMAKE_CXX_COMPILER_VERSION}")
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -Wno-deprecated-declarations -static-libstdc++ -static-libgcc -g") 
  message(STATUS "Intel FLAGS: ${CMAKE_CXX_FLAGS}")
else ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message(FATAL_ERROR "Not supported") 
endif()

############
# Git info #
############
  
# Add GIT project name  
execute_process(
  COMMAND git config --local remote.origin.url    
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_PROJECT_NAME  
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Add GIT branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD    
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Add Git hashcode  
execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(STRIP "${GIT_PROJECT_NAME} ${GIT_BRANCH} ${GIT_COMMIT_HASH}" VERSION_INFO)
message(STATUS "VERSION_INFO: ${VERSION_INFO}")   
