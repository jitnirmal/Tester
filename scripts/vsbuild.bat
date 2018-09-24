ECHO OFF
ECHO starting program
cd ..
cmake -H. -Bvsbuild
cmake --build vsbuild --
PAUSE