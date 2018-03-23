cmake_minimum_required(VERSION 3.2)

#init project version
SET(PROJECT_BUILD_NUMBER "999")

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    SET(PROJECT_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
ENDIF()

file (STRINGS ".version" PROJECT_VERSION)
file (STRINGS ".project_name" PROJECT_NAME)

configure_file(
    ${CMAKE_SOURCE_DIR}/include/version.h.in 
    ${CMAKE_SOURCE_DIR}/include/version.h
)

#init project
project (${PROJECT_NAME} VERSION ${PROJECT_VERSION}.${PROJECT_BUILD_NUMBER})


#set compiler global options
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

include_directories("${CMAKE_SOURCE_DIR}/include")

#include other cmake modules and configs
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
add_subdirectory(engine)
add_subdirectory(test)
add_subdirectory(main)
add_subdirectory(deb)


