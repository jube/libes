
set(LIBES_SRC
  Archetype.cc
  GlobalSystem.cc
  LocalSystem.cc
  Manager.cc
  Store.cc
  System.cc
  SystemVisitor.cc
)

add_library(es0 SHARED
  ${LIBES_SRC}
)

install(
  TARGETS es0
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
