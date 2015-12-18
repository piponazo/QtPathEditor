set(CMAKE_AUTOMOC ON)

file(GLOB ui_files  *.ui)
file(GLOB cpp_files *.cpp)

QT4_ADD_RESOURCES(icons ${CMAKE_SOURCE_DIR}/resources/icons.qrc)

QT4_WRAP_UI(ui_compiled ${ui_files})

add_executable(QtPathEditor WIN32 ${cpp_files} ${ui_compiled} ${icons})

target_include_directories(QtPathEditor PUBLIC  ${CMAKE_SOURCE_DIR}/src)
target_include_directories(QtPathEditor PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(QtPathEditor PRIVATE Qt4::QtCore Qt4::QtGui PathLib)
#target_link_libraries(QtPathEditor PRIVATE user32)
#target_link_libraries(QtPathEditor PRIVATE advapi32.lib user32)
#target_link_libraries(QtPathEditor PRIVATE advapi32.lib)

target_include_directories(QtPathEditor PRIVATE ${CMAKE_BINARY_DIR})
