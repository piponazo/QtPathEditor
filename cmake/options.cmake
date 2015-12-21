# Build type
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
   SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif()

if (NOT CMAKE_BUILD_TYPE)
        message( WARNING "Release build mode selected by default")
        set(CMAKE_BUILD_TYPE "Release")
endif()

# For users of Vim auto-complete packages
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

option(PRODUCE_DEBUG_INFO       "Let produce debug info on linux release compilations (-g)"             OFF)
option(PRODUCE_BETTER_EXES      "Produce smaller & faster exes. + linking time (win only)"              ON)

option(WARNINGS_ARE_ERRORS      "Treat warnings as errors"                                              OFF)
option(WARNINGS_ANSI_ISO        "Issue all the mandatory diagnostics Listed in C standard"              OFF)

option(BUILD_TESTS              "Build tests"                                                           ON)

option(BUILD_ONLY_DOC           "Configure documentation and exits from cmake stup"                     OFF)
option(INSTALL_DOC              "Install documentation in system"                                       OFF)
option(DOXY_COVERAGE            "Generate text file with the doxygen coverage"                          OFF)
option(USE_MATHJAX              "Generate doc-formulas via mathjax instead of latex"                    OFF)
option(USE_DOT                  "Diagram generation with graphviz"                                      ON)
option(USE_LATEX                "Build latex documentation"                                             OFF)
option(USE_CHM                  "Build CHM Windows documentation"                                       OFF)

set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/include")
set(CMAKE_LIB_DIRS_CONFIGCMAKE     "${CMAKE_INSTALL_PREFIX}/lib")
