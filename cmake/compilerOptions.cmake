set(EXTRA_C_FLAGS "")
set(EXTRA_C_FLAGS_RELEASE "")
set(EXTRA_C_FLAGS_DEBUG "")
set(EXTRA_EXE_LINKER_FLAGS "")
set(EXTRA_EXE_LINKER_FLAGS_RELEASE "")
set(EXTRA_EXE_LINKER_FLAGS_DEBUG "")

#Overwrite default flags
if (MSVC)
   set (CMAKE_CXX_FLAGS                "/DWIN32 /D_WINDOWS /GR /EHa")
   set (CMAKE_CXX_FLAGS_DEBUG          "/MDd /Z7 /Ob0 /Od /RTC1 /D_DEBUG")
   set (CMAKE_CXX_FLAGS_RELEASE        "/MD /O2 /Ob2 /D NDEBUG")
   set (CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})
   set (CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
   set (CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})

   set (CMAKE_EXE_LINKER_FLAGS          "/machine:x64")
   set (CMAKE_EXE_LINKER_FLAGS_RELEASE  "")
   set (CMAKE_EXE_LINKER_FLAGS_DEBUG    "/debug")
else()
    message(FATAL_ERROR "The unique compiler supported is MSVC")
endif()


#set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /Zc:wchar_t")
set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /wd4503 /wd4251")
set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /bigobj") # Increases number of sections that an object file can contain
set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /MP") # Multi-threaded compilations.
#It applies to compilations, bot not to linking or link-time code gen.

#set(EXTRA_EXE_LINKER_FLAGS "${EXTRA_EXE_LINKER_FLAGS} /time /verbose:incr") # Debug linking times
set(EXTRA_EXE_LINKER_FLAGS "${EXTRA_EXE_LINKER_FLAGS} /ignore:4049 /ignore:4217 /ignore:4099")
set(EXTRA_EXE_LINKER_FLAGS_RELEASE "${EXTRA_EXE_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libcmt")
set(EXTRA_EXE_LINKER_FLAGS_DEBUG "${EXTRA_EXE_LINKER_FLAGS_DEBUG} /OPT:NOREF /OPT:NOICF /NODEFAULTLIB:MSVCRT")

if (PRODUCE_BETTER_EXES)
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /Gy") # package individual funcions in packaged functions (COMDATs)
        # This is needed for /OPT. /ZI implies /Gy, but we are not using /ZI

        # Produces PDBs & it implies /DEBUG, but it doesn't affect optimizations
        set(EXTRA_C_FLAGS_RELEASE "${EXTRA_C_FLAGS_RELEASE} /Z7")
        set(EXTRA_EXE_LINKER_FLAGS "${EXTRA_EXE_LINKER_FLAGS} /INCREMENTAL:NO")
        set(EXTRA_EXE_LINKER_FLAGS_RELEASE "${EXTRA_EXE_LINKER_FLAGS_RELEASE} /DEBUG") # TODO - probably can be removed
        set(EXTRA_EXE_LINKER_FLAGS_RELEASE "${EXTRA_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF")
        #Remove unreferenced functions: function level linking
else()
        #It's better to disable the better EXES for the development process (faster compilations)
        set(EXTRA_EXE_LINKER_FLAGS "${EXTRA_EXE_LINKER_FLAGS} /INCREMENTAL")
endif()

if(WARNINGS_ANSI_ISO)
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /W4")
else()
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /W3")
endif()

if(WARNINGS_ARE_ERRORS)
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} /WX")
endif()

# ==========================================================
# Add user supplied extra options (optimization, etc...)
# ==========================================================
set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS}" CACHE INTERNAL "Extra compiler options")
set(EXTRA_C_FLAGS_RELEASE "${EXTRA_C_FLAGS_RELEASE}" CACHE INTERNAL "Extra compiler options for Release build")
set(EXTRA_C_FLAGS_DEBUG "${EXTRA_C_FLAGS_DEBUG}" CACHE INTERNAL "Extra compiler options for Debug build")
set(EXTRA_EXE_LINKER_FLAGS "${EXTRA_EXE_LINKER_FLAGS}" CACHE INTERNAL "Extra linker flags")
set(EXTRA_EXE_LINKER_FLAGS_RELEASE "${EXTRA_EXE_LINKER_FLAGS_RELEASE}" CACHE INTERNAL "Extra linker flags for Release build")
set(EXTRA_EXE_LINKER_FLAGS_DEBUG "${EXTRA_EXE_LINKER_FLAGS_DEBUG}" CACHE INTERNAL "Extra linker flags for Debug build")

#combine all "extra" options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_C_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${EXTRA_C_FLAGS_RELEASE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${EXTRA_C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG}")

set(CMAKE_EXE_LINKER_FLAGS         "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${EXTRA_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG   "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${EXTRA_EXE_LINKER_FLAGS_DEBUG}")
