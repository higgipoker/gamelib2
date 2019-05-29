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
#include "file.hpp"

#include <sstream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
File::File(std::string f) : file_name(std::move(f)) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
File::~File() { close(); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void File::close() {
  if (open_for_read) {
    in_file.close();
    open_for_read = false;
  }
  if (open_for_write) {
    out_file.close();
    open_for_write = false;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void File::writeLine(const std::string &line) {
  openForWrite();

  if (out_file.is_open()) {
    out_file << line.c_str() << "\n";
  } else {
    std::cout << "Unable to opne file: " << file_name.c_str();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void File::writeLine(int line) {
  std::ostringstream str;
  str << line;

  writeLine(str.str());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void File::openForWrite() {
  if (open_for_write) {
    return;
  }

  if (open_for_read) {
    in_file.close();
  }

  out_file.open(file_name.c_str(), std::ios::out);
  open_for_write = true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void File::openForRead() {
  if (open_for_read) {
    return;
  }

  if (open_for_write) {
    out_file.close();
  }

  in_file.open(file_name.c_str(), std::ios::in);
  open_for_read = true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
std::vector<std::string> File::getLines() {
  openForRead();

  // temp
  std::string line;
  while (getline(in_file, line)) {
    lines.push_back(line);
  }

  return lines;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
std::vector<std::string> File::getLines(const std::string &_ignore) {
  openForRead();

  // temp
  std::string line;
  while (getline(in_file, line)) {
    auto found = line.find(_ignore);
    if (found == std::string::npos) lines.push_back(line);
  }

  return lines;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void File::clearContents() {
  close();
  out_file.open(file_name.c_str(), std::ios::out | std::ios::trunc);
  open_for_write = true;
  close();
}

}  // namespace gamelib2
