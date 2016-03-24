cmake_minimum_required (VERSION 3.5)
project (minitasks)

# Just to check it out compilers/libraries
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
find_package(Rules) 

# Get ready for unit tests 
enable_testing()

# recursive call to code folders
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)
