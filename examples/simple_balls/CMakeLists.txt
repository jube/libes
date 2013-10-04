cmake_minimum_required(VERSION 2.6)

project(LIBES_DEMO CXX)

add_definitions(-Wall -g -O2 -std=c++11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBES0 REQUIRED libes0)
pkg_check_modules(SFML2 REQUIRED sfml-graphics)

include_directories(${LIBES0_INCLUDE_DIRS})
include_directories(${SFML2_INCLUDE_DIRS})

set(BALLS_SRC
  archetypes.cc
  balls.cc
  systems.cc
)

add_executable(balls ${BALLS_SRC})
target_link_libraries(balls ${LIBES0_LIBRARIES} ${SFML2_LIBRARIES})
