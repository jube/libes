cmake_minimum_required(VERSION 2.6)

project(LIBES CXX)

include(CPackConfig.cmake)

add_definitions(-Wall -g -O2 -std=c++11)
include_directories("${LIBES_SOURCE_DIR}/include")

add_subdirectory(lib)

find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file("${LIBES_SOURCE_DIR}/Doxyfile.cmake" "${LIBES_BINARY_DIR}/Doxyfile" @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} "${LIBES_BINARY_DIR}/Doxyfile")
endif(DOXYGEN_FOUND)

configure_file("${LIBES_SOURCE_DIR}/libes0.pc.in" "${LIBES_BINARY_DIR}/libes0.pc" @ONLY)
install(
  FILES "${LIBES_BINARY_DIR}/libes0.pc"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig"
)
