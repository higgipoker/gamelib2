#pragma once
#include <string>
#include <set>

namespace gamelib2 {

class Files {
 public:
  static std::string getWorkingDirectory();
  static std::set<std::string> getFilesInFolder(const std::string &folder);
};

}  // namespace gamelib2
