###########################################
# Configuring paths properly
###########################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(INC_DIR "${EXTERNAL_DIR}/include")
set(LIB_DIR "${EXTERNAL_DIR}/lib")
if (NOT EXTERNAL_DIR)
    message(FATAL_ERROR "EXTERNAL_DIR variable is not set")
endif()
list(APPEND CMAKE_PREFIX_PATH "${EXTERNAL_DIR}")

###########################################
# Setup Qt
###########################################

find_program(QT_QMAKE_EXECUTABLE NAMES qmake-qt4)
find_package(Qt4 COMPONENTS QtGui QtNetwork QtXml QtOpenGL QtTest QtScript QtSvg QtDeclarative REQUIRED)
include_directories(SYSTEM ${QT_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})

###########################################
# Setup Google Test Framework
###########################################

find_package(GTest REQUIRED)

add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)

# \note This stack overflow suggests that we might have different compiler
# options between googlemock and our code. If we want gtest with pthread
# it should be checked out http://tinyurl.com/nzzfrqz
add_definitions(-DGTEST_HAS_PTHREAD=0)
