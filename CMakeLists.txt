cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(university-db)

set(SRC_LIST person.cpp
             employee.cpp
             student.cpp
             database.cpp
             menu.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST} main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic -Wextra)
