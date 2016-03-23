message(STATUS "CMAKE_BUILD_TOOL = ${CMAKE_BUILD_TOOL}")
message(STATUS "CMAKE_COMMAND = ${CMAKE_COMMAND}")

# Useful commands 
set(INVOKE_CMAKE_SCRIPT ${CMAKE_COMMAND} -DLOCAL_SOURCE_DIR="${CMAKE_SOURCE_DIR}" -P) 
set(INVOKE_CMAKE_SCRIPT_HARDCODED ${CMAKE_COMMAND} -DLOCAL_SOURCE_DIR="${CMAKE_SOURCE_DIR}" -DVERSION_HARDCODED=TRUE -P) 
set(COPY_DIFF ${CMAKE_COMMAND} -E copy_if_different) 
set(COPY_DIR ${CMAKE_COMMAND} -E copy_directory) 
set(REMOVE_DIR ${CMAKE_COMMAND} -E remove_directory)
set(REMOVE ${CMAKE_COMMAND} -E remove -f)
set(ENV_CMD ${CMAKE_COMMAND} -E env ${EXTRA_ARG})

# clean & regenerate git commit hash
add_custom_target(clean_git_commit_hash ${REMOVE} ${PROJECT_BINARY_DIR}/Doxyfile
   COMMAND ${REMOVE} ${PROJECT_BINARY_DIR}/header.tex
   COMMAND ${REMOVE_DIR} ${PROJECT_BINARY_DIR}/latex
   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

############# DOCUMENTATION ##############

find_package(Doxygen)
if(DOXYGEN_FOUND)

 # TARGET
 set(TMP_PDF_FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.pdf)
 set(TMP_HTML_DIR ${CMAKE_BINARY_DIR}/html)
 set(PDF_FILE ${CMAKE_SOURCE_DIR}/doc/${CMAKE_PROJECT_NAME}.pdf)
 set(HTML_DIR ${CMAKE_SOURCE_DIR}/doc/html)

 # make image
 #add_custom_target( image ${INVOKE_CMAKE_SCRIPT} ${PROJECT_SOURCE_DIR}/image/CMakeLists.txt
 #   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
 #)

 # make doc --> ALL
 add_custom_target( doc ALL ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
   COMMAND ${ENV_CMD} ${CMAKE_BUILD_TOOL} -Wno-dev -f ${PROJECT_BINARY_DIR}/latex/Makefile -C ${PROJECT_BINARY_DIR}/latex
   COMMAND ${REMOVE_DIR} ${TMP_LATEX_DIR}
   COMMAND ${COPY_DIFF} ${PROJECT_BINARY_DIR}/latex/refman.pdf ${TMP_PDF_FILE}
   COMMAND ${COPY_DIR} ${PROJECT_BINARY_DIR}/html ${HTML_DIR}
   #DEPENDS image
   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
 )

 # make install_doc
# add_custom_target( get_doc echo "TMP_PDF_FILE=${TMP_PDF_FILE}" 
#   COMMAND echo "PDF_FILE=${PDF_FILE}"
#   COMMAND echo "HTML_DIR=${HTML_DIR}"
#   COMMAND ${COPY_DIFF} ${TMP_PDF_FILE} ${PDF_FILE} 
#   COMMAND ${COPY_DIR} ${TMP_HTML_DIR} ${HTML_DIR} 
#   DEPENDS doc
# )
	
endif(DOXYGEN_FOUND)
