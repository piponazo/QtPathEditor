# QtPathEditor
Windows application for editing the PATH environment variable (Qt based).

This application is mostly oriented for windows developers who need to manage the binary paths often.
Windows has a very plain and monolitic editor in which you only can edit a list of paths separated by
semicolons. There are some free applications that improves notably the experience for handling those
paths, but I always missed some features in such applications. This application means to be an
open-source project covering all those missing features that windows developers have always yearned
for (specially those coming from other Operative Systems, such as Linux).

> Note: Windows 10 has greatly improved the PATH editor in comparison with their predecesors. However
> this editor still have some other features that you can find interesting. 

## Features

TODO

## Internals

Ultimately, this application write/read to/from the windows registry. However, in order to implement
all the application features other information is stored in a configuration file.

## Dependencies

The unique dependency this project has is Qt5. It could have been done without too much troubles
with Qt4 or directly using the Windows API, but in the future I would like to create the user
interface with QML in order to research that technology.

An optional dependency is googletest for the unit tests created during the development of the
library code. Note that the application business logic and the UI code is seperated.

CMake has been used to configure the project. In order to detect the project dependencies correctly
you will need to run cmake specifying where to find them:

cmake ../ -DCMAKE_PREFIX_PATH=/c/Qt/Qt5.5.1/msvc2015_64/ -DGTEST_ROOT=/d/Dev/Windows/msvc14/
