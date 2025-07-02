cmake_minimum_required(VERSION 3.16)
project(nox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------------------------------------------------------
# Fetch GoogleTest
# ----------------------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ----------------------------------------------------------------------------
# Lexer Library
# ----------------------------------------------------------------------------

add_library(lexer
  src/lexer.cpp
  src/lexer.h
)

target_include_directories(lexer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)

# ----------------------------------------------------------------------------
# Test Suite
# ----------------------------------------------------------------------------

enable_testing()

add_executable(lexer_test
  src/lexer_test.cpp
)

target_link_libraries(lexer_test
  PRIVATE
    lexer
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lexer_test)
