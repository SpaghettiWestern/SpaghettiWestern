#ifndef PATHGENERATOR_H
#define PATHGENERATOR_H

#include <map>
#include <vector>
#include <queue>
#include <cmath>

#include "Util.h"
#include "GameBoardStructure.h"

struct distanceCoordinate{
	distanceCoordinate(const Coordinate& coord, int g_score, int f_score);

	Coordinate coord;
	int g_score;
	int f_score;
};

class CoordinateComparison{
	public:
	CoordinateComparison();
	bool operator() (const distanceCoordinate& lhs, const distanceCoordinate &rhs) const;
};

class PathGenerator{
private:
	std::shared_ptr<GameBoardStructure>& board;

	std::priority_queue<distanceCoordinate, std::vector<distanceCoordinate>, CoordinateComparison> pq_open_set;

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
	void traverseNeighbor(const Coordinate& neighbor);

	void reconstructPath(const Coordinate& start);

public:
	PathGenerator(std::shared_ptr<GameBoardStructure>& board);
	int estimateDistance(const Coordinate& start, const Coordinate& end);

	bool findPath(const Coordinate& start, const Coordinate& end);
	std::vector<Coordinate> getPath();
};


#endif
