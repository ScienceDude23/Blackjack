cmake_minimum_required(VERSION 3.14)
project(blackjack LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
# Header-only library target
add_library(cards INTERFACE)
target_include_directories(cards INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
 
# ---- Tests ------------------------------------------------------------------
# include(CTest) calls enable_testing() and adds the BUILD_TESTING option
# (configure with -DBUILD_TESTING=OFF to skip tests and the GoogleTest download).
include(CTest)
 
if(BUILD_TESTING)
  include(FetchContent)
 
  if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)  # use extraction time for URL downloads
  endif()
 
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  # Windows: don't override the parent project's runtime settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
 
  add_executable(cards_tests test_cards.cpp)
  target_link_libraries(cards_tests PRIVATE cards GTest::gtest_main)
 
  if(MSVC)
    target_compile_options(cards_tests PRIVATE /W4)
  else()
    target_compile_options(cards_tests PRIVATE -Wall -Wextra -Wpedantic)
  endif()
 
  include(GoogleTest)
  gtest_discover_tests(cards_tests)
endif()
 
