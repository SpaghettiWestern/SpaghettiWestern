#include "BoardColumn.h"


BoardColumn::BoardColumn(std::vector<std::unique_ptr<BoardSpace>>& columnCells) : columnCells(columnCells){
	height = columnCells.size();
}


std::vector<std::shared_ptr<BoardSpace>>& BoardColumn::getColumnCells(){
	return columnCells;
}


void BoardColumn::setColumnCells(std::vector<std::unique_ptr<BoardSpace>>& cells){
	columnCells = cells;
	height = columnCells.size();
}

int BoardColumn::getHeight() const {
	return height;
}
