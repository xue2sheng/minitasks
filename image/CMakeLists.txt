cmake_minimum_required(VERSION 3.5)

# Useful commands 
set(INVOKE_CMAKE_SCRIPT ${CMAKE_COMMAND} -P) 
set(COPY_DIFF ${CMAKE_COMMAND} -E copy_if_different) 
set(COPY_DIR ${CMAKE_COMMAND} -E copy_directory) 
set(REMOVE_DIR ${CMAKE_COMMAND} -E remove_directory)
set(REMOVE ${CMAKE_COMMAND} -E remove -f)
set(ENV_CMD ${CMAKE_COMMAND} -E env ${EXTRA_ARG})

set(IMAGE_DIR "${CMAKE_SOURCE_DIR}/image")
set(UML_DIR "${CMAKE_SOURCE_DIR}/image/uml")
set(ROOT_DIR "${CMAKE_SOURCE_DIR}/image")

set(BUILD_IMAGE_DIR "${CMAKE_BINARY_DIR}/image")

if(APPLE)

     ### Graphviz dot
     if($ENV{GRAPHVIZ_DOT} MATCHES ".*dot.*$")
       set(DOT $ENV{GRAPHVIZ_DOT})
     else()
       set(DOT /usr/local/bin/dot)
     endif()

     ### PlantUML
     if($ENV{PLANTUMLJAR} MATCHES ".*jar$")
       set(PLANTUML java -jar $ENV{PLANTUMLJAR} -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -v -o ${BUILD_IMAGE_DIR})
       set(METADATA java -jar $ENV{PLANTUMLJAR} -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -metadata)
     else()
       set(PLANTUML java -jar /opt/plantuml/plantuml.jar -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -v -o ${BUILD_IMAGE_DIR})
       set(METADATA java -jar /opt/plantuml/plantuml.jar -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -metadata)
     endif()

elseif(UNIX)

     ### Graphviz dot
     if($ENV{GRAPHVIZ_DOT} MATCHES ".*dot.*$")
       set(DOT $ENV{GRAPHVIZ_DOT})
     else()
       set(DOT /usr/bin/dot)
     endif()

     ### PlantUML
     if($ENV{PLANTUMLJAR} MATCHES ".*jar$")
       set(PLANTUML java -jar $ENV{PLANTUMLJAR} -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -v -o ${BUILD_IMAGE_DIR})
       set(METADATA java -jar $ENV{PLANTUMLJAR} -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -metadata)
     else()
       set(PLANTUML java -jar /opt/plantuml/plantuml.jar -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -v -o ${BUILD_IMAGE_DIR})
       set(METADATA java -jar /opt/plantuml/plantuml.jar -graphvizdot ${DOT} -DUML_DIR=${UML_DIR} -metadata)
     endif()

endif()
message(STATUS "PLANTUML=${PLANTUML}")
 
#### invoke PlantUML ####
execute_process(
  COMMAND ${PLANTUML} README.md src/*.* src/basic/*.* doc/*.*  
  WORKING_DIRECTORY ${ROOT_DIR} 
)

#### list of images to copy & check ###
set(COPY_LIST "")
set(CHECK_LIST "")

#### list of images ####
file(GLOB IMAGE_LIST RELATIVE ${BUILD_IMAGE_DIR} ${BUILD_IMAGE_DIR}/*.png)

#### list of images already created ####
file(GLOB ALREADY_IMAGE_LIST RELATIVE ${IMAGE_DIR} ${IMAGE_DIR}/*.png)

#### copy if new ####
#### else check ####
foreach(PNG ${IMAGE_LIST})
 list(FIND ALREADY_IMAGE_LIST ${PNG} FOUND)
 if(FOUND LESS 0)
   list(APPEND COPY_LIST ${PNG})
 else()
   list(APPEND CHECK_LIST ${PNG})
 endif(FOUND LESS 0)
endforeach()
list(REMOVE_DUPLICATES COPY_LIST)
list(REMOVE_DUPLICATES CHECK_LIST)

#### Grab metainfo ####
foreach(PNG ${CHECK_LIST})
  execute_process(
   COMMAND ${METADATA} ${BUILD_IMAGE_DIR}/${PNG}  
   OUTPUT_VARIABLE NEW_UML 
   WORKING_DIRECTORY ${BUILD_IMAGE_DIR} 
   OUTPUT_STRIP_TRAILING_WHITESPACE 
  )
  string(FIND "${NEW_UML}" "@startuml" NEW_STARTUML)
  if(NEW_STARTUML GREATER 0)
    string(FIND "${NEW_UML}" "@enduml" NEW_ENDUML)
    math(EXPR NEW_LENGTH "${NEW_ENDUML} - ${NEW_STARTUML} + 8 ") # @enduml\n got 8 chars

    execute_process(
      COMMAND ${METADATA} ${IMAGE_DIR}/${PNG}  
      OUTPUT_VARIABLE OLD_UML 
      WORKING_DIRECTORY ${BUILD_IMAGE_DIR} 
      OUTPUT_STRIP_TRAILING_WHITESPACE 
    )

    string(FIND "${OLD_UML}" "@startuml" OLD_STARTUML)
    if(OLD_STARTUML GREATER 0)
      string(FIND "${OLD_UML}" "@enduml" OLD_ENDUML)
      math(EXPR OLD_LENGTH "${OLD_ENDUML} - ${OLD_STARTUML} + 8") # @enduml\n got 8 chars

      if("${NEW_LENGTH}" STREQUAL "${OLD_LENGTH}")

        ### there could be a character change ###
        string(SUBSTRING "${NEW_UML}" "${NEW_STARTUML}" "${NEW_LENGTH}" NEW_UML)
        string(SUBSTRING "${OLD_UML}" "${OLD_STARTUML}" "${OLD_LENGTH}" OLD_UML)

        string(COMPARE NOTEQUAL "${NEW_UML}" "${OLD_UML}" DIFFERENT)
        if(DIFFERENT)
          list(APPEND COPY_LIST ${PNG})    
        endif(DIFFERENT)

      else("${NEW_LENGTH}" STREQUAL "${OLD_LENGTH}")
        # not need in process metadata
        list(APPEND COPY_LIST ${PNG})    
      endif("${NEW_LENGTH}" STREQUAL "${OLD_LENGTH}")

    else(OLD_STARTUML GREATER 0)
      # copy just in case if not metadata
      list(APPEND COPY_LIST ${PNG})    
    endif(OLD_STARTUML GREATER 0)

  else(NEW_STARTUML GREATER 0)
    # copy just in case if not metadata
    list(APPEND COPY_LIST ${PNG})    
  endif(NEW_STARTUML GREATER 0)

endforeach()
list(REMOVE_DUPLICATES COPY_LIST)
message(STATUS "COPY_LIST=${COPY_LIST}")

#### copy if different (or if there is not metadata to check) ####
foreach(PNG ${IMAGE_LIST})
  execute_process(
   COMMAND ${COPY_DIFF} ${BUILD_IMAGE_DIR}/${PNG} ${IMAGE_DIR}/${PNG}
   WORKING_DIRECTORY ${CMAKE_BINARY_DIR} 
  )
endforeach()
