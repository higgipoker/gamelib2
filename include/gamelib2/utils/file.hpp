/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace gamelib2 {

class File {
 public:
  File(std::string f);
  ~File();
  void clearContents();
  void writeLine(const std::string& line);
  void writeLine(int line);
  void close();
  std::vector<std::string> getLines();
  std::vector<std::string> getLines(const std::string& _ignore);

 protected:
  std::string file_name;
  std::ofstream out_file;
  std::ifstream in_file;

  bool open_for_read = false;
  bool open_for_write = false;

  void openForWrite();
  void openForRead();

  std::vector<std::string> lines;
};

}  // namespace gamelib2
