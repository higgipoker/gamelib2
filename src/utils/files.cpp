#include "files.hpp"

// #define WINDOWS  // uncomment this line to use it for windows
#ifdef WINDOWS
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
//
// -----------------------------------------------------------------------------
std::vector<std::string> Files::getFilesInFolder(const std::string &folder) {
  std::vector<std::string> out;

  for (auto &p : std::filesystem::directory_iterator(folder)) {
    out.push_back(p.path());
    std::cout << p.path() << std::endl;
  }

  return out;
}
}  // namespace gamelib2
