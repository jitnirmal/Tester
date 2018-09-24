ECHO OFF
ECHO starting program
cd ../build
#DEL /F /Q /A *
#cmake .. -G "MinGW Makefiles" -Dgtest_disable_pthreads=On
mingw32-make

cd test\testOrder
testOrder.exe
PAUSE