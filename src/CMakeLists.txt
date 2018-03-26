###
#global
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    add_definitions(-DBOOST_TEST_DYN_LINK)
###
#foo library
    add_library(foo foo.cpp )

###
#Unit tests
    add_executable(test_foo test.cpp)
    add_test(test_foo test_foo)

        target_link_libraries(  test_foo
                            ${Boost_LIBRARIES}
                            foo
                        )

###
#Main
    add_executable(${PROJECT_NAME} main.cpp )
    target_link_libraries(  ${PROJECT_NAME} 
                            ${Boost_LIBRARIES}
                            foo
                        )

    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

