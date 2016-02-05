#include "PathInterpolater.h"

PathInterpolater::PathInterpolater(){
	out_path.clear();
}

void PathInterpolater::generatePath(const ScreenCoordinate& start, const ScreenCoordinate& dest, double speed){
	out_path.clear();

	double x_dist = dest.first - start.first;
	double y_dist = dest.second - start.second;
	double dist = sqrt(x_dist*x_dist + y_dist*y_dist);
	if(dist <= 0){
		return;
	}

	double x_step = speed * (x_dist/dist);
	double y_step = speed * (y_dist/dist);

	out_path.push_back(dest);
	for(double dist_traveled = 0; dist_traveled < dist-speed; dist_traveled+=speed){
		ScreenCoordinate loc(out_path.back().first-x_step, out_path.back().second-y_step);
		out_path.push_back(loc);
	}
	out_path.push_back(start);
}

void PathInterpolater::transferPath(std::vector<ScreenCoordinate>& dest_path){
	dest_path.swap(out_path);
	out_path.clear();
}

const std::vector<ScreenCoordinate>& PathInterpolater::getPath() const{
	return out_path;
}
