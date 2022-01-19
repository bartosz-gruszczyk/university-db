cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(university-db)

#GTest download
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_LIST address.cpp
             person.cpp
             employee.cpp
             student.cpp
             database.cpp
             data_generator.cpp
             menu.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST} main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic -Wextra)

# Tests executable
add_executable(${PROJECT_NAME}-ut ${SRC_LIST} tests.cpp)
target_link_libraries(${PROJECT_NAME}-ut gtest_main)
enable_testing()

add_test(NAME ${PROJECT_NAME}-test COMMAND ${PROJECT_NAME}-ut)