file(GLOB MARKDOWN *.md)
file(GLOB SRC *.cpp *.hpp)
add_library(basic SHARED ${SRC} ${MARKDOWN})

# to install directly from complied code
install(TARGETS basic LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT library)
