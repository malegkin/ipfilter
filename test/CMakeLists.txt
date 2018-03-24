
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories(${Boost_INCLUDE_DIR})


find_package(Boost COMPONENTS unit_test_framework REQUIRED)

FILE(GLOB _SOURCES_CPP "*.cpp")
FOREACH (_SOURCE_CPP ${_SOURCES_CPP})

    get_filename_component( _TEST_NAME "${_SOURCE_CPP}" NAME_WE )

    add_executable(${_TEST_NAME} "${_TEST_NAME}.cpp")

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

    add_test(NAME "TEST_${_TEST_NAME}" COMMAND ${_TEST_NAME})

ENDFOREACH()






