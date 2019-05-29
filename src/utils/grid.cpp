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
#include "grid.hpp"
#include <algorithm>

namespace gamelib2 {

//  --------------------------------------------------
//  init
//  --------------------------------------------------
void Grid::init(int _x, int _y, int w, int h, int c, int r) {
  x = _x;
  y = _y;
  SECTOR_COLUMNS = c;
  SECTOR_ROWS = r;
  width = w;
  height = h;

  center_column = SECTOR_COLUMNS / 2;
  center_row = SECTOR_ROWS / 2;

  sectors.clear();
  sectors_reversed.clear();
  sector_width = width / SECTOR_COLUMNS;
  sector_height = height / SECTOR_ROWS;

  int cnt = 0;
  for (int i = 0; i < SECTOR_ROWS; i++) {
    for (int j = 0; j < SECTOR_COLUMNS; j++) {
      sectors.push_back(
          Sector((j * sector_width) + x, (i * sector_height) + y, i, j));
      sectors_reversed.push_back(cnt);
      cnt++;
    }
  }

  std::reverse(sectors_reversed.begin(), sectors_reversed.end());
}

//  --------------------------------------------------
//  getSectorFromGrid
//  --------------------------------------------------
int Grid::getSectorFromGrid(int col, int row) {
  return (row * SECTOR_COLUMNS) + col;
}

//  --------------------------------------------------
//  getSector
//  --------------------------------------------------
int Grid::getSector(int _x, int _y) {
  _x -= x;
  _y -= y;

  int sector = 0;

  int col = _x / sector_width;
  int row = _y / sector_height;

  sector = (col + (SECTOR_COLUMNS * row));

  if (sector < 0 || sector >= (int)sectors.size()) {
    sector = -1;
  }

  return sector;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int Grid::getSector(const Vector3 &pos) {
  return getSector(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

//  --------------------------------------------------
//  colsFromCenter
//  --------------------------------------------------
int Grid::colsFromCenter(int sector) {
  return sectors[sector].col - center_column;
}

//  --------------------------------------------------
//  rowsFromCenter
//  --------------------------------------------------
int Grid::rowsFromCenter(int sector) {
  return sectors[sector].row - center_row;
}

//  --------------------------------------------------
//  offsetSectorByx
//  --------------------------------------------------
int Grid::offsetSectorByx(int sector, int cols) {
  int min = getFirstInRow(sector);
  int max = getLastInRow(sector);

  int new_sector = sector + cols;

  if (new_sector < min)
    new_sector = min;
  else if (new_sector > max)
    new_sector = max;

  return new_sector;
}

//  --------------------------------------------------
//  offsetSectorByy
//  --------------------------------------------------
int Grid::offsetSectorByy(int sector, int rows) {
  int min = getFirstInCol(sector);
  int max = getLastInCol(sector);

  int new_sector = sector + (SECTOR_COLUMNS * rows);

  if (new_sector < min)
    new_sector = min;
  else if (new_sector > max)
    new_sector = max;

  return new_sector;
}

//  --------------------------------------------------
//  getFirstInRow
//  --------------------------------------------------
int Grid::getFirstInRow(int sector) {
  return sectors[sector].row * SECTOR_COLUMNS;
}

//  --------------------------------------------------
//  getLastInRow
//  --------------------------------------------------
int Grid::getLastInRow(int sector) {
  return (sectors[sector].row * SECTOR_COLUMNS) + SECTOR_COLUMNS - 1;
}

//  --------------------------------------------------
//  getFirstInCol
//  --------------------------------------------------
int Grid::getFirstInCol(int sector) { return sectors[sector].col; }

//  --------------------------------------------------
//  getLastInCol
//  --------------------------------------------------
int Grid::getLastInCol(int sector) {
  return (SECTOR_ROWS - 1) * SECTOR_COLUMNS + sectors[sector].col;
}

//  --------------------------------------------------
//  getRandoPointInSector
//  --------------------------------------------------
Vector3 Grid::getRandoPointInSector(int sector) {
  int min_x = sectors[sector].x;

  int min_y = sectors[sector].y;

  Vector3 p;
  p.x = static_cast<float>(min_x + rand() % sector_width);
  p.y = static_cast<float>(min_y + rand() % sector_height);

  return p;
}

//  --------------------------------------------------
//  getCol
//  --------------------------------------------------
int Grid::getCol(int sector) {
  int answer = sector % SECTOR_COLUMNS;
  return answer;
}

//  --------------------------------------------------
//  getRow
//  --------------------------------------------------
int Grid::getRow(int sector) { return sector / SECTOR_COLUMNS; }

//  --------------------------------------------------
//  shiftInRow
//  --------------------------------------------------
int Grid::shiftInRow(int sector, int shift) {
  int first_sector_in_row = ((getRow(sector)) * SECTOR_COLUMNS);
  int last_sector_in_row = ((getRow(sector) + 1) * SECTOR_COLUMNS) - 1;

  int ret = sector + shift;
  if (ret > last_sector_in_row) {
    ret = last_sector_in_row;
  }
  if (ret < first_sector_in_row) {
    ret = first_sector_in_row;
  }

  return ret;
}

//  --------------------------------------------------
//  shiftInCol
//  --------------------------------------------------
int Grid::shiftInCol(int sector, int shift) {
  int first_sector_in_col = getCol(sector);
  int last_sector_in_col = SECTOR_COLUMNS * (SECTOR_ROWS - 1) + getCol(sector);

  int ret = sector + (SECTOR_COLUMNS * shift);

  if (ret < first_sector_in_col) {
    ret = first_sector_in_col;
  }
  if (ret > last_sector_in_col) {
    ret = last_sector_in_col;
  }

  return ret;
}

//  --------------------------------------------------
//  sectorValid
//  --------------------------------------------------
bool Grid::sectorValid(int sector) {
  if (sector < 0) {
    return false;
  }

  if (sector >= (int)sectors.size()) {
    return false;
  }

  return true;
}

//  --------------------------------------------------
//  randomSector
//  --------------------------------------------------
int Grid::randomSector() { return rand() % sectors.size(); }

//  --------------------------------------------------
//  mirrorUpDown
//  --------------------------------------------------
int Grid::mirrorUpDown(int sector) {
  int distance_to_center = center_row - getRow(sector);

  return shiftInCol(sector, distance_to_center * 2);
}

//  --------------------------------------------------
//  mirrorLeftRight
//  --------------------------------------------------
int Grid::mirrorLeftRight(int sector) {
  int distance_to_center = center_column - getCol(sector);

  return shiftInRow(sector, distance_to_center * 2);
}

//  --------------------------------------------------
//  mirrorSector
//  --------------------------------------------------
int Grid::mirrorSector(int sector) {
  return mirrorLeftRight(mirrorUpDown(sector));
}

//  --------------------------------------------------
//  getReversed
//  --------------------------------------------------
int Grid::getReversed(int sector) { return sectors_reversed[sector]; }

//  --------------------------------------------------
//  getSectorCenter
//  --------------------------------------------------
Vector3 Grid::getSectorCenter(int sector) {
  Vector3 center;

  if (sector < (int)sectors.size()) {
    center.x = static_cast<float>(sectors[sector].x + (sector_width / 2));
    center.y = static_cast<float>(sectors[sector].y + (sector_height / 2));
  }

  return center;
}

}  // namespace gamelib2
