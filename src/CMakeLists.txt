cmake_minimum_required(VERSION 2.6)

project(LIBES CXX)

option(COMPILER_IS_NOT_CXX11_READY "The compiler is not ready yet for C++11 (GCC < 4.8, Clang < 3.3, MSVC)" TRUE)

include(CPackConfig.cmake)

if (NOT MSVC)
  add_definitions(-Wall -g -O2)
  if (COMPILER_IS_NOT_CXX11_READY)
    add_definitions(-std=c++0x) # equivalent of -std=c++11, but the later works only for GCC >= 4.7
  else (COMPILER_IS_NOT_CXX11_READY)
    add_definitions(-std=c++11)
  endif (COMPILER_IS_NOT_CXX11_READY)
endif (NOT MSVC)

configure_file("${CMAKE_SOURCE_DIR}/include/es/Support.h.in" "${CMAKE_BINARY_DIR}/include/es/Support.h")

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_BINARY_DIR}/include")

add_subdirectory(lib)

find_package(Doxygen)

if (DOXYGEN_FOUND)
  configure_file("${CMAKE_SOURCE_DIR}/Doxyfile.cmake" "${CMAKE_BINARY_DIR}/Doxyfile" @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile")
endif (DOXYGEN_FOUND)

configure_file("${CMAKE_SOURCE_DIR}/libes0.pc.in" "${CMAKE_BINARY_DIR}/libes0.pc" @ONLY)
install(
  FILES "${CMAKE_BINARY_DIR}/libes0.pc"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig"
)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/include/es"
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)

install(
  DIRECTORY "${CMAKE_BINARY_DIR}/include/es"
  DESTINATION include
)
