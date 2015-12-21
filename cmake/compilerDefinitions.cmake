##########################################
# Qt library definitions
##########################################
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        add_definitions(-DQT_NO_DEBUG)
        add_definitions(-DQT_NO_DEBUG_OUTPUT)
        add_definitions(-DQT_NO_WARNING_OUTPUT)
else()
        add_definitions(-DQT_DEBUG)
endif()

##########################################
# Windows definitions
##########################################

# \todo check if we still need this in msvc2015
add_definitions(-DQ_COMPILER_INITIALIZER_LISTS)

add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
add_definitions(
       -DNOMINMAX
       -D_CRT_SECURE_NO_WARNINGS
       -D_SCL_SECURE_NO_WARNINGS
       -D_USE_MATH_DEFINES
       -DUNICODE
       -D_UNICODE
)

# Reduce build times
add_definitions(-DWIN32_LEAN_AND_MEAN)  # exclude APIs such as Cryptography, DDE, RPC, Shell and Sockets
# exclude many other APIS
add_definitions(-DNOCOMM -DNOWINOFFSETS -DNOOPENFILE -DNOSERVICE -DNOSOUND -DNOATOM)
add_definitions(-DNOWH -DNOKANJI -DNOHELP -DNOPROFILER -DNOMCX)

# Support at least Windows Vista
add_definitions(-D_WIN32_WINNT=0x0600 -DPSAPI_VERSION=1)
