#ifndef PATHGENERATOR_H
#define PATHGENERATOR_H

#include <map>
#include <vector>
#include <queue>
#include <cmath>

#include "Util.h"
#include "GameBoardStructure.h"

class PathGenerator{
private:
	std::shared_ptr<GameBoardStructure>& board;

	std::map<Coordinate, bool> closed_set;
	std::map<Coordinate, bool> open_set;
	std::map<Coordinate, Coordinate> came_from;
	std::map<Coordinate, int> g_score;
	std::map<Coordinate, int> f_score;

	std::vector<Coordinate> path;

	Coordinate curr;
	Coordinate end;

	void resetSets();
	Coordinate getSmallestOpen();
	void traverseNeighbors();
	void traverseNeighbor(Coordinate neighbor);

	void reconstructPath(Coordinate start);

public:
	PathGenerator(std::shared_ptr<GameBoardStructure>& board);
	int estimateDistance(Coordinate& start, Coordinate& end);

	bool findPath(Coordinate start, Coordinate end);
	std::vector<Coordinate> getPath();
};


#endif
