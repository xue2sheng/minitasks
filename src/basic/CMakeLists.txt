file(GLOB MARKDOWN *.md)
file(GLOB SRC *.cpp *.hpp)
add_library(basic SHARED ${SRC} ${MARKDOWN})

message(STATUS "basic czmqpp ${CZMQPP_INCLUDE_DIRS}")

include_directories( ${ZeroMQ_INCLUDE_DIRS} ${CZMQ_INCLUDE_DIRS} ${CZMQPP_INCLUDE_DIRS} )
target_link_libraries(basic ${ZeroMQ_LIBRARIES} ${CZMQ_LIBRARIES} ${CZMQPP_LIBRARIES} )

# to install directly from complied code
install(TARGETS basic LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT library)
