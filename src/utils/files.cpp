#include "files.hpp"
//#define WINDOWS  // uncomment this line to use it for windows
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <filesystem>
#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
//  getWorkingDirectory
// -----------------------------------------------------------------------------
std::string Files::getWorkingDirectory() {
  char buff[FILENAME_MAX];
  GetCurrentDir(static_cast<char *>(buff), FILENAME_MAX);
  std::string current_working_dir(static_cast<char *>(buff));
  return current_working_dir;
}

// -----------------------------------------------------------------------------
// getFilesInFolder
// -----------------------------------------------------------------------------
std::set<std::string> Files::getFilesInFolder(std::string folder) {
  std::set<std::string> out;

  for (auto p : std::filesystem::directory_iterator(folder)) {
    std::cout << p.path() << std::endl;
    out.insert(p.path().string());
  }

  // sort alphabetically by default

  return out;
}
}  // namespace gamelib2
