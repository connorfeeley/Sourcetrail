# ${CMAKE_SOURCE_DIR}/tests/integration/lib/CMakeLists.txt

set(
  test_lib_names
  RefreshInfoGeneratorTestSuite
  SourceGroupTestSuite
  SqliteBookmarkStorageTestSuite
  SqliteIndexStorageTestSuite
  StorageTestSuite)

foreach(test_name IN LISTS test_lib_names)
  add_executable(${test_name} ${test_name}.cpp)

  target_link_libraries(
    ${test_name}
    PUBLIC
      Catch2::Catch2WithMain
      Qt5::Core
      Sourcetrail::messaging
      $<$<BOOL:${BUILD_CXX_LANGUAGE_PACKAGE}>:Sourcetrail::lib_cxx>)

  set_target_properties(
    ${test_name}
    PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

  # automatically discover ${test_name} that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
  # to whatever you want, or use different for different binaries
  catch_discover_tests(
    ${test_name}
    TEST_PREFIX
    "integration."
    REPORTER XML
    OUTPUT_DIR .
    OUTPUT_PREFIX "integration."
    OUTPUT_SUFFIX .xml
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test")
endforeach()
