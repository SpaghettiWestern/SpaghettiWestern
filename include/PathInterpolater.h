#ifndef PATHINTERPOLATER_H
#define PATHINTERPOLATER_H

#include <vector>
#include <math.h>

#include "Util.h"

class PathInterpolater{
private:
	std::vector<Coordinate2D<double>> out_path;

public:
	PathInterpolater();

	void generatePath(const Coordinate2D<double>& start, const Coordinate2D<double>& dest, double speed);
	void transferPath(std::vector<Coordinate2D<double>>& dest_path);

	const std::vector<Coordinate2D<double>>& getPath() const;
};



#endif
