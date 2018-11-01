#pragma once
#include <string>
#include <vector>

namespace gamelib2 {

class Files {
 public:
  static std::string getWorkingDirectory();
  static std::vector<std::string> getFilesInFolder(const std::string &folder);
};

}  // namespace gamelib2
