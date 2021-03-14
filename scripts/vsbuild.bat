ECHO OFF
ECHO starting program
cd ..
cmake -H. -B..\..\vsbuildOut -Drun_gcov=0
cmake --build ..\..\vsbuildOut -- /maxcpucount:8
PAUSE