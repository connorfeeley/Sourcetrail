# ${}/src/external/CMakeLists.txt
add_library(CppSQLite3 sqlite/CppSQLite3.cpp)
add_library(CppSQLite::CppSQLite3 ALIAS CppSQLite3)
target_link_libraries(
  CppSQLite3
  PUBLIC
    ${SQLITE_LIBRARIES})
target_include_directories(
  CppSQLite3
  SYSTEM PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/sqlite)
set_source_files_properties(
  CppSQLite3
  PROPERTIES
    COMPILE_FLAGS "-w")