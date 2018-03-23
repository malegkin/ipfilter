####
# Create targets
file(GLOB_RECURSE _SOURCES_CPP "*.cpp")
#add_executable(engine ${_SOURCES_CPP} )
add_library(engine ${_SOURCES_CPP} )

