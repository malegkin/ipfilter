find_package(TCLAP REQUIRED)
include_directories(${TCLAP_INCLUDE_DIR})

####
# Create targets
file(GLOB_RECURSE _SOURCES_CPP "*.cpp")
add_executable(${PROJECT_NAME} ${_SOURCES_CPP} )

target_link_libraries(  ${PROJECT_NAME} 
                        ${Boost_LIBRARIES}
                        engine
                    )

#
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

