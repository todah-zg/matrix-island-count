cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5ab508a01f9eb089207ee87fd547d290da39d015.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  matrix_test
  src/Matrix.cpp
  test/matrix_test.cc
)
target_link_libraries(
  matrix_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)
