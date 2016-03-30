################################################
# generate version.h from template version.h.in 
################################################

# Create .hpp version file with VERSION_INFO 
set(VERSION_HPP_IN "${CMAKE_SOURCE_DIR}/src/version.hpp.in")
set(VERSION_HPP_OUT "${CMAKE_SOURCE_DIR}/src/version.hpp")
configure_file(${VERSION_HPP_IN} ${VERSION_HPP_OUT})

################################################
# trigger different subfolder compilations
################################################

file(GLOB MARKDOWN *.md)
file(GLOB SRC *.cpp *.hpp)
add_subdirectory(basic)
find_package( Boost REQUIRED COMPONENTS program_options )
include_directories( ${Boost_INCLUDE_DIRS} )
add_executable(${CMAKE_PROJECT_NAME}  ${SRC} ${MARKDOWN})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_PROGRAM_OPTIONS_LIBRARY} dl )

# install #
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT binary)

