ECHO OFF
ECHO starting program
cd ..
cmake -H. -B..\vsbuildTester -Drun_gcov=0
cmake --build ..\vsbuildTester -- /maxcpucount:8
PAUSE