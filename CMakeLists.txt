cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(university-db)

set(SRC_LIST student.cpp
             database.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST} main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic -Wextra)
