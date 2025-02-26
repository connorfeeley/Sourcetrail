# ${CMAKE_SOURCE_DIR}/src/lib_cxx/tests/CMakeLists.txt
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

set(test_cxx_names
      CompilationDatabaseTestSuite
      IncludeDirectiveTestSuite)

foreach(test_name IN LISTS test_cxx_names)
  add_executable(${test_name} ${test_name}.cpp)

  target_link_libraries(
    ${test_name}
    PUBLIC
    testHelper
    lib::mocks
    GTest::gtest
    GTest::gtest_main
    Sourcetrail::lib
    Sourcetrail::lib_cxx)

  gtest_discover_tests(
    ${test_name}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test/"
    TEST_PREFIX "unittests.")
endforeach()