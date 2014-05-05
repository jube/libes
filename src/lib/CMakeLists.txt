
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

set_target_properties(es0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
)

install(
  TARGETS es0
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
