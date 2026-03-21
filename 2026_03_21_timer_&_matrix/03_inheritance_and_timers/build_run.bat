@echo off
chcp 1251 > log
del log

set NAME=inheritance_and_timers_test
set EXE=%NAME%.exe

set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

set SOURCES="main.cpp"

g++ -O0 "%CHARSET%" "%SOURCES%" -o %EXE%

%EXE%
