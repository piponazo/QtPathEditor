call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64

rmdir buildRelease /s /q
rmdir buildDebug   /s /q
mkdir buildRelease
mkdir buildDebug

cd buildRelease
cmake ../ -GNinja^
   -DCMAKE_BUILD_TYPE=Release^
   -DCMAKE_PREFIX_PATH=c:/Qt/Qt5.5.1/msvc2015_64/^
   -DGTEST_ROOT=d:/Dev/Windows/msvc14/

cd ..\buildDebug
cmake ../ -GNinja^
   -DCMAKE_BUILD_TYPE=Debug^
   -DCMAKE_PREFIX_PATH=c:/Qt/Qt5.5.1/msvc2015_64/^
   -DGTEST_ROOT=d:/Dev/Windows/msvc14/

cd ..
