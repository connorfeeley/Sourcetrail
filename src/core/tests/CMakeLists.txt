# ${CMAKE_SOURCE_DIR}/src/core/tests/CMakeLists.txt
set(
  test_lib_names
  FileManagerTestSuite
  FilePathFilterTestSuite
  FilePathTestSuite
  FileSystemTestSuite

  ConfigManagerTestSuite)

foreach(test_name IN LISTS test_lib_names)
  add_executable(${test_name} ${test_name}.cpp)

  target_link_libraries(
    ${test_name}
    PUBLIC
      Catch2::Catch2WithMain
      Sourcetrail::core)

  set_target_properties(
    ${test_name}
    PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

  # automatically discover ${test_name} that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
  # to whatever you want, or use different for different binaries
  catch_discover_tests(
    ${test_name}
    TEST_PREFIX "unittests."
    REPORTER XML
    OUTPUT_DIR .
    OUTPUT_PREFIX "unittests."
    OUTPUT_SUFFIX .xml
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test")
endforeach()

target_link_libraries(
  FileSystemTestSuite
    PRIVATE
      Sourcetrail::lib_utility)

target_link_libraries(
  FileManagerTestSuite
    PRIVATE
      Sourcetrail::lib_utility)

set(gtest_lib_names
    LoggerTestSuite
    TextAccessTestSuite)

foreach(test_name IN LISTS gtest_lib_names)
  add_executable(${test_name} ${test_name}.cpp)

  target_link_libraries(
    ${test_name}
    PUBLIC
      GTest::gmock
      GTest::gtest
      GTest::gtest_main
      lib::mocks
      Sourcetrail::core)

  gtest_discover_tests(
    ${test_name}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test/"
    TEST_PREFIX "unittests.")
endforeach()

