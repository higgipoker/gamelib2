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

/**
 * @brief The File class
 */
class File {
 public:
  /**
   * @brief File
   * @param f
   */
  File(std::string f);
  ~File();

  /**
   * @brief clearContents
   */
  void clearContents();

  /**
   * @brief writeLine
   * @param line
   */
  void writeLine(const std::string& line);

  /**
   * @brief writeLine
   * @param line
   */
  void writeLine(int line);

  /**
   * @brief close
   */
  void close();

  /**
   * @brief getLines
   * @return
   */
  std::vector<std::string> getLines();

  /**
   * @brief getLines
   * @param _ignore
   * @return
   */
  std::vector<std::string> getLines(const std::string& _ignore);

 protected:
  std::string file_name;
  std::ofstream out_file;
  std::ifstream in_file;

  bool opened_for_read = false;
  bool opened_for_write = false;

  /**
   * @brief openForWrite
   */
  void open_for_write();

  /**
   * @brief openForRead
   */
  void open_for_read();

  std::vector<std::string> lines;
};

}  // namespace gamelib2
