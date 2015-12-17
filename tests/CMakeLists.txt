if(NOT GTEST_FOUND)

   message(WARNING "GTest is not installed in your system so tests can't be compiled")

elseif(BUILD_TESTS)

    include_directories(${PROJECT_BINARY_DIR}/)         # including PathLib_export.h
    include_directories(${PROJECT_SOURCE_DIR}/src)      # including the library headers
    include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})   # including the Gtest headers

    add_subdirectory(unitary)

    # Generate a single application including all the tests
    add_executable(tests_unitary
        test_unitary.cpp
        ${srcs_unit_all}
    )

    target_link_libraries(tests_unitary PRIVATE
        ${GTEST_BOTH_LIBRARIES}
        PathLib
    )

endif()
