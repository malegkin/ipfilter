cmake_minimum_required(VERSION 3.2)


#init project version
SET(PROJECT_BUILD_NUMBER "999")

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    SET(PROJECT_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
ENDIF()

file (STRINGS ".version" PROJECT_VERSION)
file (STRINGS ".project_name" PROJECT_NAME)

#init project
project (${PROJECT_NAME} VERSION ${PROJECT_VERSION}.${PROJECT_BUILD_NUMBER})

set(ENV{_TEST_RESOURCES_DIR} "${CMAKE_SOURCE_DIR}/resources")

#set compiler global options
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

enable_testing()
add_subdirectory(src)
add_subdirectory(deb)

