cmake_minimum_required(VERSION 3.7)
project(Password_Generator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp passwords.h passwords.cpp dict.txt)
add_executable(Password_Generator ${SOURCE_FILES})