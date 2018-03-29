###
#global

    find_package(Boost COMPONENTS unit_test_framework  filesystem REQUIRED)
    find_package(OpenSSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIRS})

    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    add_definitions(-DBOOST_TEST_DYN_LINK)
###
#foo library
    add_library(foo foo.cpp )

###
#Unit tests
    #prepare test vectors;

#    execute_process(COMMAND "${CMAKE_SOURCE_DIR}/src/resources/generate_ips.sh" 1000000 
#                    OUTPUT_FILE "${CMAKE_SOURCE_DIR}/src/resources/1M.tsv"
 #   )

#    execute_process(COMMAND "${CMAKE_SOURCE_DIR}/src/resources/generate_ips.sh" 10000 
#                    OUTPUT_FILE "${CMAKE_SOURCE_DIR}/src/resources/ips.tsv"
#    )
#    execute_process(COMMAND "${CMAKE_SOURCE_DIR}/src/resources/sort_ips.sh"  
#                    "${CMAKE_SOURCE_DIR}/src/resources/ips.tsv" 
#                    OUTPUT_FILE "${CMAKE_SOURCE_DIR}/src/resources/sorted_ips.tsv"
#    )     

    add_executable(test_foo test.cpp)
    add_test(test_foo test_foo "${CMAKE_SOURCE_DIR}/src/resources")
    set_tests_properties(test_foo PROPERTIES TIMEOUT 30)
    

        target_link_libraries(  test_foo
                            ${Boost_LIBRARIES}
                            ${OPENSSL_LIBRARIES}
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

