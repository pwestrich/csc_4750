@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\TDM-GCC-64\bin

::g++ -c String.cpp
::g++ -c Tokens.cpp
g++ -c ReadFile.cpp
g++ -c WriteFile.cpp
g++ -c Keyboard.cpp
g++ -c Matrix.cpp
g++ -c Poly.cpp
::g++ -c CD.cpp
::g++ -c Song.cpp
g++ -c Integer.cpp
g++ -c Double.cpp
::g++ -c HighPerformanceCounter.cpp
g++ -c Permutation.cpp

ar -r libCSC2110.a *.o






