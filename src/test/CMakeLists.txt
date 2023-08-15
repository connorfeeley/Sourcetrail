# ${CMAKE_SOURCE_DIR}/src/test/CMakeLists.txt
add_library(catch_main OBJECT test_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2WithMain Sourcetrail::core)
target_include_directories(
  catch_main
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/helper
    ${CMAKE_SOURCE_DIR}/src/lib_gui/utility/
    ${CMAKE_SOURCE_DIR}/src/lib_gui/utility/path_detector/
    ${LIB_INCLUDE_PATHS}
    ${LIB_GUI_INCLUDE_PATHS}
    ${CMAKE_BINARY_DIR}/src/lib)

# ========================================================
add_library(testHelper helper/TestFileRegister.cpp)
target_link_libraries(
  testHelper
    PUBLIC
    Sourcetrail::core
    Sourcetrail::scheduling)
target_include_directories(
  testHelper
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/helper
    ${LIB_INCLUDE_PATHS})

# ========================================================
set(
  test_lib_names
  CommandlineTestSuite
  GraphTestSuite
  HierarchyCacheTestSuite
  LogManagerTestSuite
  LowMemoryStringMapTestSuite
  MatrixBaseTestSuite
  MatrixDynamicBaseTestSuite
  NetworkProtocolHelperTestSuite
  ProjectSettingsTestSuite
  SearchIndexTestSuite
  SettingsMigratorTestSuite
  SettingsTestSuite
  SharedMemoryTestSuite
  UtilityTestSuite)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

foreach(test_name IN LISTS test_lib_names)
  add_executable(${test_name} ${test_name}.cpp)

  target_link_libraries(
    ${test_name}
    PUBLIC
      testHelper
      Catch2::Catch2WithMain
      Sourcetrail::lib
      Sourcetrail::lib_gui
      $<$<BOOL:${BUILD_CXX_LANGUAGE_PACKAGE}>:Sourcetrail::lib_cxx>)

  target_include_directories(
    ${test_name}
    PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
      ${LIB_INCLUDE_PATHS}
      ${LIB_UTILITY_INCLUDE_PATHS}
      ${LIB_GUI_INCLUDE_PATHS}
      ${EXTERNAL_INCLUDE_PATHS}
      ${CMAKE_BINARY_DIR}/src/lib)

  # automatically discover ${test_name} that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
  # to whatever you want, or use different for different binaries
  catch_discover_tests(
    ${test_name}
    TEST_PREFIX
    "unittests."
    REPORTER XML
    OUTPUT_DIR .
    OUTPUT_PREFIX "unittests."
    OUTPUT_SUFFIX .xml
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test")
endforeach()

set(test_lib_names
    AppPathTestSuite
    IndexerCompositeTestSuite
    ResourcePathsTestSuite
    UserPathsTestSuite
    Vector2TestSuite
    Vector4TestSuite)

foreach(test_name IN LISTS test_lib_names)
  add_executable(${test_name} ${test_name}.cpp)

  target_link_libraries(
    ${test_name}
    PUBLIC
      lib::mocks
      GTest::gmock
      GTest::gtest
      GTest::gtest_main
      Sourcetrail::lib)
  
  set_target_properties(
    ${test_name}
    PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

  gtest_discover_tests(
    ${test_name}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test/"
    TEST_PREFIX "unittests.")
endforeach()
# ========================================================
set(test_core_names "")

foreach(test_name IN LISTS test_core_names)
  add_executable(${test_name} ${test_name}.cpp)

  target_link_libraries(
    ${test_name}
    PUBLIC
      testHelper
      Catch2::Catch2WithMain
      Sourcetrail::core)

  # automatically discover ${test_name} that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
  # to whatever you want, or use different for different binaries
  catch_discover_tests(
    ${test_name}
    TEST_PREFIX
    "unittests."
    REPORTER XML
    OUTPUT_DIR .
    OUTPUT_PREFIX "unittests."
    OUTPUT_SUFFIX .xml
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test")
endforeach()
