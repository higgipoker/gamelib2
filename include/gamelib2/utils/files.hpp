#pragma once
#include <set>
#include <string>

namespace gamelib2 {

class Files {
 public:
  static std::string getWorkingDirectory();
  static std::set<std::string> getFilesInFolder(std::string folder);
};

}  // namespace gamelib2
