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
#pragma	once
#include	"../math/vector.hpp"
#include	<vector>
namespace	gamelib2	{

struct	Sector	{

				Sector(int	_x,	int	_y,	int	_row,	int	_col)	{
								x	=	_x;
								y	=	_y;
								row	=	_row;
								col	=	_col;
				}

				int	x=0;
				int	y=0;
				int	row=0;
				int	col=0;
};

class	Grid	{
public:
				void	init(int	_x,	int	_y,	int	w,	int	h,	int	c,	int	r);
				int	getSectorFromGrid(int	col,	int	row);
				int	getSector(int	x,	int	y);
				int	colsFromCenter(int	sector);
				int	rowsFromCenter(int	sector);
				int	offsetSectorByx(int	sector,	int	cols);
				int	offsetSectorByy(int	sector,	int	rows);
				int	getFirstInRow(int	sector);
				int	getLastInRow(int	sector);
				int	getFirstInCol(int	sector);
				int	getLastInCol(int	sector);
				int	getCol(int	sector);
				int	getRow(int	sector);
				int	shiftInRow(int	sector,	int	shift);
				int	shiftInCol(int	sector,	int	shift);
				int	randomSector();
				int	mirrorUpDown(int	sector);
				int	mirrorLeftRight(int	sector);
				int	mirrorSector(int	sector);
				int	getReversed(int	sector);
				bool	sectorValid(int	sector);
				Vector3	getRandoPointInSector(int	sector);
				Vector3	getSectorCenter(int	sector);

				std::vector<Sector>	sectors;
				int	sector_width=0;
				int	sector_height=0;

private:
				int	x=0;
				int	y=0;
				int	width=0;
				int	height=0;
				int	SECTOR_COLUMNS=0;
				int	SECTOR_ROWS=0;
				int	center_column=0;
				int	center_row=0;
				std::vector<int>	sectors_reversed;
};
}	// namespace gamlib2
