###########################################
# Setup Qt
###########################################

find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)

###########################################
# Setup Google Test Framework
###########################################

find_package(GTest      REQUIRED)
add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)

# \note This stack overflow suggests that we might have different compiler
# options between googlemock and our code. If we want gtest with pthread
# it should be checked out http://tinyurl.com/nzzfrqz
#add_definitions(-DGTEST_HAS_PTHREAD=0)
