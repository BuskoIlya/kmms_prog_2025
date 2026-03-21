@echo off
chcp 1251 > log
del log

set NAME=main
set EXE=%NAME%.exe

set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

set SOURCES="%NAME%.cpp matrix.cpp cache_optimized_matrix.cpp"

g++ "%CHARSET%" "%SOURCES%" -o %EXE%

%EXE%
