##################################################################
# Detect and setup source files
##################################################################
file(GLOB sources *.cpp *.h)

add_library(PathLib SHARED ${sources})

# Make all the symbols hidden, so we have to explicitly make the API public
#set_target_properties(PathLib PROPERTIES CXX_VISIBILITY_PRESET hidden)
generate_export_header(PathLib EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/PathLib_export.h")

target_include_directories(PathLib PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(PathLib PUBLIC Qt5::Core)
