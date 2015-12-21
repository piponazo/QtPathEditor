##################################################################
# Detect and setup source files
##################################################################
file(GLOB_RECURSE libcore_sources_cxx *.cpp *.h)

add_library(PathLib    ${libcore_sources_cxx})

# Make all the symbols hidden, so we have to explicitly make the API public
set_target_properties(PathLib PROPERTIES CXX_VISIBILITY_PRESET hidden)
#generate_export_header(core EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/core_export.h")
