#ifndef BOARDCOLUMN_H
#define BOARDCOLUMN_H

#include <BoardCell.h>
#include "BoardFloor.h"

#include "GL/gl.h"

#include <vector>

class BoardColumn {
public:
	BoardColumn(std::vector<std::unique_ptr<BoardSpace>>& columnCells);

	std::vector<std::shared_ptr<BoardSpace>>& getColumnCells();
	void setColumnCells(std::vector<std::unique_ptr<BoardSpace>>& cells);
	int getHeight() const;

private:

	int height;
	GLuint lateralTexture;
	std::unique_ptr<BoardFloor> groundFloor;
	std::vector<std::shared_ptr<BoardSpace>>& columnCells;


};

#endif
