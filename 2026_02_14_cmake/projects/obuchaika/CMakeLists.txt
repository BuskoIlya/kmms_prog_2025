project(obuchaika)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=windows-1251")

set(SOURCES 
	main.cpp
	menu_functions.cpp
	menu_items.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
