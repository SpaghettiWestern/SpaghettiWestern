#include "PathInterpolater.h"

PathInterpolater::PathInterpolater(){
	out_path.clear();
}

void PathInterpolater::generatePath(const Coordinate2D<double>& start, const Coordinate2D<double>& dest, double speed){
	out_path.clear();

	double x_dist = dest.x - start.x;
	double y_dist = dest.y - start.y;
	double dist = sqrt(x_dist*x_dist + y_dist*y_dist);
	if(dist <= 0){
		return;
	}

	double x_step = speed * (x_dist/dist);
	double y_step = speed * (y_dist/dist);

	out_path.push_back(dest);
	for(double dist_traveled = 0; dist_traveled < dist-speed; dist_traveled+=speed){
		ScreenCoordinate loc(out_path.back().x-x_step, out_path.back().y-y_step);
		out_path.push_back(loc);
	}
	out_path.push_back(start);
}

void PathInterpolater::transferPath(std::vector<Coordinate2D<double>>& dest_path){
	dest_path.swap(out_path);
	out_path.clear();
}

const std::vector<Coordinate2D<double>>& PathInterpolater::getPath() const{
	return out_path;
}
