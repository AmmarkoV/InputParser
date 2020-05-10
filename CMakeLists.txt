project( InputParser )  
cmake_minimum_required(VERSION 3.5) 


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
 
add_library(InputParser STATIC InputParser.cpp InputParser_C.c)   


target_link_libraries(InputParser rt dl m)
set_target_properties(InputParser PROPERTIES DEBUG_POSTFIX "D")
set_target_properties(InputParser PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )


add_library(InputParser_C SHARED InputParser_C.c)
target_link_libraries(InputParser_C rt dl m)
set_target_properties(InputParser_C PROPERTIES DEBUG_POSTFIX "D")
set_target_properties(InputParser_C PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )


 

add_executable(InputParserTester InputParser_C_Tester/main.c)   
target_link_libraries(InputParserTester rt dl m InputParser_C)
set_target_properties(InputParserTester PROPERTIES DEBUG_POSTFIX "D")
set_target_properties(InputParserTester PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )

