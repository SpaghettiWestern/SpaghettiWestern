#ifndef PATHINTERPOLATER_H
#define PATHINTERPOLATER_H

#include <vector>
#include <math.h>

#include "Util.h"

class PathInterpolater{
private:
	std::vector<ScreenCoordinate> out_path;

public:
	PathInterpolater();

	void generatePath(const ScreenCoordinate& start, const ScreenCoordinate& dest, double speed);
	void transferPath(std::vector<ScreenCoordinate>& dest_path);

	const std::vector<ScreenCoordinate>& getPath() const;
};



#endif
