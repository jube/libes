cmake_minimum_required(VERSION 2.6)

project(LIBES_DEMO CXX)

add_definitions(-Wall -g -O2 -std=c++11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBES0 REQUIRED libes0)
pkg_check_modules(SFML2 REQUIRED sfml-graphics)


find_path(BOX2D_INCLUDE_DIRS Box2D/Box2D.h)
find_library(BOX2D_LIBRARIES Box2D)

message(STATUS "Box2D:")
message(STATUS "  - include dirs: ${BOX2D_INCLUDE_DIRS}")
message(STATUS "  - libraries: ${BOX2D_LIBRARIES}")

include_directories(${LIBES0_INCLUDE_DIRS})
include_directories(${SFML2_INCLUDE_DIRS})
include_directories(${BOX2D_INCLUDE_DIRS})

set(BALLS_SRC
  archetypes.cc
  balls.cc
  systems.cc
)

add_executable(balls ${BALLS_SRC})
target_link_libraries(balls ${LIBES0_LIBRARIES} ${SFML2_LIBRARIES} ${BOX2D_LIBRARIES})
