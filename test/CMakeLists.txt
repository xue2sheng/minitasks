################################################
# generate version.h from template version.h.in
################################################

# Add GIT info
execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "GIT hashcode: ${GIT_COMMIT_HASH}")

# Create .hpp version file
set(VERSION_HPP_IN "${CMAKE_SOURCE_DIR}/test/version.hpp.in")
set(VERSION_HPP_OUT "${CMAKE_SOURCE_DIR}/test/version.hpp")
configure_file(${VERSION_HPP_IN} ${VERSION_HPP_OUT})

####################
# Compile test cases
####################

file(GLOB MARKDOWN *.md)
file(GLOB SRC *.cpp *.hpp)
find_package( Boost REQUIRED COMPONENTS unit_test_framework )
include_directories( ${Boost_INCLUDE_DIRS} )
add_executable(unitTest ${SRC} ${MARKDOWN})
target_link_libraries(unitTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
add_test(testMain unitTest)
