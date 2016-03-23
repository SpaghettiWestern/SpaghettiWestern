#ifndef PATHGENERATOR_H
#define PATHGENERATOR_H

#include <map>
#include <vector>
#include <queue>
#include <cmath>

#include "Util.h"
#include "GameBoardStructure.h"

struct distanceCoordinate{
	distanceCoordinate(const Coordinate3D<int>& coord, int g_score, int f_score);

	Coordinate3D<int> coord;
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

	std::map<Coordinate3D<int>, bool> closed_set;
	std::map<Coordinate3D<int>, bool> open_set;
	std::map<Coordinate3D<int>, Coordinate3D<int>> came_from;
	std::map<Coordinate3D<int>, int> g_score;
	std::map<Coordinate3D<int>, int> f_score;

	std::vector<Coordinate3D<int>> path;

	Coordinate3D<int> curr;
	Coordinate3D<int> end;

	void resetSets();
	void traverseNeighbors();
	void traverseNeighbor(const Coordinate3D<int>& neighbor);

	void reconstructPath(const Coordinate3D<int>& start);

public:
	PathGenerator(std::shared_ptr<GameBoardStructure>& board);
	int estimateDistance(const Coordinate3D<int>& start, const Coordinate3D<int>& end);

	bool findPath(const Coordinate3D<int>& start, const Coordinate3D<int>& end);
	std::vector<Coordinate3D<int>> getPath();
};


#endif
