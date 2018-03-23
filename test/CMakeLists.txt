
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories(${Boost_INCLUDE_DIR})

enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

FILE(GLOB _SOURCES_CPP "*.cpp")
FOREACH (_SOURCE_CPP ${_SOURCES_CPP})

    get_filename_component( _TEST_NAME "${_SOURCE_CPP}" NAME_WE )

    add_executable(${_TEST_NAME} "${_TEST_NAME}.cpp")

#    add_executable(test_ip_parser test_ip_parser.cpp)
   # set_target_properties(${_TEST_NAME} PROPERTIES
 #   set_target_properties(test_ip_parser PROPERTIES
    #    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    #    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    #)    
    target_compile_definitions(${_TEST_NAME} PUBLIC
                                BOOST_TEST_DYN_LINK
                                )                                

    target_include_directories( ${_TEST_NAME} PUBLIC 
                                ${Boost_INCLUDE_DIR}                            
    )
    
 
    target_link_libraries( ${_TEST_NAME}
                            ${Boost_LIBRARIES}
                            engine
    )

#    target_link_libraries(test_ip_parser
#         ${Boost_LIBRARIES}
#        engine
 #   )



    add_test(${_TEST_NAME} ${_TEST_NAME})

ENDFOREACH()







