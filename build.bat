@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\TDM-GCC-64\bin;c:\Windows
set PROJECT_PATH=%cd%

mingw32-make -j 4 %2 DRIVE_LETTER="%DRIVE_LETTER%" PROJECT_DIR="%PROJECT_PATH%"
