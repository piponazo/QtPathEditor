project(QtPathEditor)
cmake_minimum_required(VERSION 3.3)

include(cmake/versions.cmake              REQUIRED)
include(cmake/options.cmake               REQUIRED)

include(cmake/findDependencies.cmake      REQUIRED)
include(cmake/compilerDefinitions.cmake   REQUIRED)
include(cmake/compilerOptions.cmake       REQUIRED)

include(GenerateExportHeader)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)

include(cmake/printInfo.cmake             REQUIRED)
