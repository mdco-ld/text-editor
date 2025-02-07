cmake_minimum_required(VERSION 3.10)

project(editor VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
	src/main.cpp
	src/terminal.cpp
	include/terminal.hpp
	src/ui/base.cpp
	include/ui/base.hpp
	src/buffer.cpp
	include/buffer.hpp
	src/utils.cpp
	include/utils.hpp
	src/logger.cpp
	include/logger.hpp
	src/input/base.cpp
	include/input/base.hpp
	src/ui/box.cpp
	include/ui/box.hpp
	src/ui/status.cpp
	include/ui/status.hpp
	src/window.cpp
	include/window.hpp
	src/ui/rect.cpp
	include/ui/rect.hpp
)

add_executable(editor ${SOURCES})

include_directories(include)

target_compile_options(editor PRIVATE -Wall -Wextra -pedantic -Werror -DDEVELOPMENT)
