// STL
#include <algorithm>
#include <any>
#include <iterator>
#include <string>
#include <vector>
// catch2
#include <catch2/catch_all.hpp>
// internal
#include "FileSystem.h"
#include "utility.h"

namespace {
bool isInFiles(const std::set<FilePath>& files, const FilePath& filename) {
  return std::end(files) != files.find(filename);
}

bool isInFileInfos(const std::vector<FileInfo>& infos, const std::wstring& filename) {
  return std::any_of(std::cbegin(infos),
                     std::cend(infos),
                     [wFileName = FilePath(filename).getCanonical().wstr()](const auto& info) {
                       return info.path.getAbsolute().wstr() == wFileName;
                     });
}

bool isInFileInfos(const std::vector<FileInfo>& infos,
                   const std::wstring& filename,
                   const std::wstring& filename2) {
  return std::any_of(std::cbegin(infos),
                     std::cend(infos),
                     [wFileName = FilePath(filename).getCanonical().wstr(),
                      wFileName2 = FilePath(filename2).getCanonical().wstr()](const auto& info) {
                       const auto wPath = info.path.wstr();
                       return wPath == wFileName || wPath == wFileName2;
                     });
}
}    // namespace

// NOLINTNEXTLINE(cert-err58-cpp)
TEST_CASE("find cpp files", "[core]") {
  std::vector<std::wstring> cppFiles = utility::convert<FilePath, std::wstring>(
      FileSystem::getFilePathsFromDirectory(FilePath(L"data/FileSystemTestSuite"), {L".cpp"}),
      [](const FilePath& filePath) { return filePath.wstr(); });

  REQUIRE(cppFiles.size() == 4);
  REQUIRE(utility::containsElement<std::wstring>(cppFiles, L"data/FileSystemTestSuite/main.cpp"));
  REQUIRE(utility::containsElement<std::wstring>(
      cppFiles, L"data/FileSystemTestSuite/Settings/sample.cpp"));
  REQUIRE(
      utility::containsElement<std::wstring>(cppFiles, L"data/FileSystemTestSuite/src/main.cpp"));
  REQUIRE(
      utility::containsElement<std::wstring>(cppFiles, L"data/FileSystemTestSuite/src/test.cpp"));
}

TEST_CASE("find h files", "[core]") {
  std::vector<std::wstring> headerFiles = utility::convert<FilePath, std::wstring>(
      FileSystem::getFilePathsFromDirectory(FilePath(L"data/FileSystemTestSuite"), {L".h"}),
      [](const FilePath& filePath) { return filePath.wstr(); });

  REQUIRE(headerFiles.size() == 3);
  REQUIRE(
      utility::containsElement<std::wstring>(headerFiles, L"data/FileSystemTestSuite/tictactoe.h"));
  REQUIRE(utility::containsElement<std::wstring>(
      headerFiles, L"data/FileSystemTestSuite/Settings/player.h"));
  REQUIRE(
      utility::containsElement<std::wstring>(headerFiles, L"data/FileSystemTestSuite/src/test.h"));
}

TEST_CASE("find all source files", "[core]") {
  std::vector<std::wstring> sourceFiles = utility::convert<FilePath, std::wstring>(
      FileSystem::getFilePathsFromDirectory(
          FilePath(L"data/FileSystemTestSuite"), {L".h", L".hpp", L".cpp"}),
      [](const FilePath& filePath) { return filePath.wstr(); });

  REQUIRE(sourceFiles.size() == 8);
}

// TODO(Hussein): Fix next test
#if DISABLED
TEST_CASE("find file infos", "[core]") {
#ifndef _WIN32
  std::vector<FilePath> directoryPaths;
  directoryPaths.emplace_back(L"./data/FileSystemTestSuite/src");

  std::vector<FileInfo> files = FileSystem::getFileInfosFromPaths(
      directoryPaths, {L".h", L".hpp", L".cpp"}, false);

  REQUIRE(files.size() == 3);
  REQUIRE(isInFileInfos(files, L"./data/FileSystemTestSuite/src/test.cpp"));
  REQUIRE(isInFileInfos(files, L"./data/FileSystemTestSuite/src/main.cpp"));
  REQUIRE(isInFileInfos(files, L"./data/FileSystemTestSuite/src/test.h"));
#endif
}
#endif

#if DISABLED
TEST_CASE("find file infos with symlinks", "[core]") {
#  ifndef _WIN32
  std::vector<FilePath> directoryPaths;
  directoryPaths.emplace_back(L"./data/FileSystemTestSuite/src");

  const auto files = FileSystem::getFileInfosFromPaths(
      directoryPaths, {L".h", L".hpp", L".cpp"}, true);

  REQUIRE(files.size() == 5);
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/Settings/player.h",
                        L"./data/FileSystemTestSuite/player.h"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/Settings/sample.cpp",
                        L"./data/FileSystemTestSuite/sample.cpp"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/main.cpp",
                        L"./data/FileSystemTestSuite/src/Settings/src/main.cpp"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/test.cpp",
                        L"./data/FileSystemTestSuite/src/Settings/src/test.cpp"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/test.h",
                        L"./data/FileSystemTestSuite/src/Settings/src/test.h"));
#  endif
}
#endif

// TODO(Hussein): Fix next test
#if DISABLED
TEST_CASE("find symlinked directories") {
#  ifndef _WIN32
  std::vector<FilePath> directoryPaths;
  directoryPaths.emplace_back("./data/FileSystemTestSuite/src");

  const auto dirs = FileSystem::getSymLinkedDirectories(directoryPaths);

  REQUIRE(dirs.size() == 2);
#  endif
}
#endif
