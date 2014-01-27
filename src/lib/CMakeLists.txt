
set(LIBES_SRC
  CustomSystem.cc
  EventHandler.cc
  GlobalSystem.cc
  LocalSystem.cc
  Manager.cc
  SingleSystem.cc
  Store.cc
  System.cc
  Type.cc
)

add_library(es0 SHARED
  ${LIBES_SRC}
)

install(
  TARGETS es0
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
