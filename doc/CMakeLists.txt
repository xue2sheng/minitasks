message(STATUS "CMAKE_BUILD_TOOL = ${CMAKE_BUILD_TOOL}")
message(STATUS "CMAKE_COMMAND = ${CMAKE_COMMAND}")

# Useful commands 
set(INVOKE_CMAKE_SCRIPT ${CMAKE_COMMAND} -P) 
set(COPY_DIFF ${CMAKE_COMMAND} -E copy_if_different) 
set(COPY_DIR ${CMAKE_COMMAND} -E copy_directory) 
set(ENV_CMD ${CMAKE_COMMAND} -E env ${EXTRA_ARG})

############# DOCUMENTATION ##############

find_package(Doxygen)
if(DOXYGEN_FOUND)

if (DOXYGEN_VERSION VERSION_LESS 1.8.11)

     message(WARNING "Doxygen version must be at least 1.8.11 so skipped documentation")

else (DOXYGEN_VERSION VERSION_LESS 1.8.11)

 # Templates for documentation files
 set(DOXYFILE_IN "${CMAKE_SOURCE_DIR}/doc/Doxyfile.in")
 set(DOXYFILE_OUT "${CMAKE_BINARY_DIR}/Doxyfile")
 set(HEADER_TEX_IN "${CMAKE_SOURCE_DIR}/doc/header.tex.in")
 set(HEADER_TEX_OUT "${CMAKE_BINARY_DIR}/header.tex")
 set(MD_FILTER_AWK_IN "${CMAKE_SOURCE_DIR}/doc/md_filter.awk.in")
 set(MD_FILTER_AWK_OUT "${CMAKE_BINARY_DIR}/md_filter.awk")

 # extra environment info
 site_name(CMAKE_HOSTNAME)
 set(GIT_SYSTEM "$ENV{USER}@${CMAKE_HOSTNAME}")

 # list of folder to be processed
 set( DOXYFILE_INPUT00 "${CMAKE_SOURCE_DIR}")
 set( DOXYFILE_INPUT01 "${CMAKE_SOURCE_DIR}/src")
 set( DOXYFILE_INPUT02 "${CMAKE_SOURCE_DIR}/test")
 set( DOXYFILE_INPUT03 "${CMAKE_SOURCE_DIR}/doc")
 set( DOXYFILE_INPUT04 "${CMAKE_SOURCE_DIR}/tools")
 set( DOXYFILE_INPUT05 "${CMAKE_SOURCE_DIR}/image")
 set( CMAKE_HEADER_OUT "${CMAKE_BINARY_DIR}/header.tex")

 # On *nix systems, it's easier to use an external awk script
 # This way, we're not limited on the starting words of our sections (we can use random values for references)
 # Besides, it's possible to target only specific Markdown files
 # So it'll be easier to 'target' other entries, i.e. java files, in the future
 set(DOXYFILE_IMAGE_PATH "IMAGE_PATH = ${CMAKE_SOURCE_DIR}/image")
 set(DOXYFILE_INPUT_FILTER "INPUT_FILTER =") # future use on Windows where "awk" is not a default option
 set(DOXYFILE_FILTER_PATTERNS "FILTER_PATTERNS = \"*.md=\\\"awk -f ${MD_FILTER_AWK_OUT}\\\"\" ")

 # Create templates
 configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT})
 configure_file(${HEADER_TEX_IN} ${HEADER_TEX_OUT})
 configure_file(${MD_FILTER_AWK_IN} ${MD_FILTER_AWK_OUT})

 # TARGET
 set(TMP_PDF_FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.pdf)
 set(TMP_HTML_DIR ${CMAKE_BINARY_DIR}/html)

 # make image
 add_custom_target( image ${INVOKE_CMAKE_SCRIPT} ${PROJECT_SOURCE_DIR}/image/CMakeLists.txt
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
 )

 # make doc 
 add_custom_target( doc ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
   COMMAND ${ENV_CMD} ${CMAKE_BUILD_TOOL} -Wno-dev -f ${PROJECT_BINARY_DIR}/latex/Makefile -C ${PROJECT_BINARY_DIR}/latex
   COMMAND ${COPY_DIFF} ${PROJECT_BINARY_DIR}/latex/refman.pdf ${TMP_PDF_FILE}
   COMMAND ${COPY_DIR} ${PROJECT_BINARY_DIR}/html ${HTML_DIR}
   DEPENDS image
   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
 )

 # make doc and copy at doc folder
 add_custom_target( doc_and_deploy echo "TMP_PDF_FILE=${TMP_PDF_FILE}" 
   COMMAND echo "PDF_FILE=${PDF_FILE}"
   COMMAND echo "HTML_DIR=${HTML_DIR}"
   COMMAND ${COPY_DIFF} ${TMP_PDF_FILE} ${PDF_FILE} 
   COMMAND ${COPY_DIR} ${TMP_HTML_DIR} ${HTML_DIR} 
   DEPENDS doc
   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
 )
	
  endif (DOXYGEN_VERSION VERSION_LESS 1.8.11)

elseif(DOXYGEN_FOUND)
   message(WARNING "Doxygen not installed; skipped documentation")
endif(DOXYGEN_FOUND)
