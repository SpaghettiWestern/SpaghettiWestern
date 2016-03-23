#ifndef PATHINTERPOLATER_H
#define PATHINTERPOLATER_H

#include <vector>
#include <math.h>

#include "Util.h"

class PathInterpolater{
private:
	std::vector<Coordinate2D<double>> out_path;

	void deepCopy(const PathInterpolater& other);

public:
	PathInterpolater();
	PathInterpolater(const PathInterpolater& other);

	PathInterpolater& operator=(const PathInterpolater& other);

	void generatePath(const Coordinate2D<double>& start, const Coordinate2D<double>& dest, double speed);
	void transferPath(std::vector<Coordinate2D<double>>& dest_path);

	const std::vector<Coordinate2D<double>>& getPath() const;
};



#endif
