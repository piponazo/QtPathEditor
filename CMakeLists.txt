project(QtPathEditor)
cmake_minimum_required(VERSION 3.3)

include(cmake/versions.cmake              REQUIRED)
include(cmake/options.cmake               REQUIRED)

include(cmake/findDependencies.cmake      REQUIRED)
include(cmake/compilerDefinitions.cmake   REQUIRED)
include(cmake/compilerOptions.cmake       REQUIRED)

add_subdirectory(src)

include(cmake/printInfo.cmake             REQUIRED)
